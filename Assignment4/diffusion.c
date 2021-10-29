#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

int main(int argc, char *argv[])
{
    // ========================= Parsing arguments =========================
    int iter_num = 0;      // iteration number
    float diff_const = 0.; // diffusion constant
    // parsing arguments
    if (argc != 3)
    {
        fprintf(stderr, "Error: Wrong Syntax. Should be in form:\n./diffusion -n[number_of_iterations] -d[diffusion_constant]\n");
        exit(0);
    }
    char *ptr_n, *ptr_d;
    for (size_t ix = 1; ix < argc; ix++)
    {
        ptr_n = strchr(argv[ix], 'n');
        ptr_d = strchr(argv[ix], 'd');
        if (ptr_n)
            iter_num = strtol(++ptr_n, NULL, 10);
        else if (ptr_d)
            diff_const = strtof(++ptr_d, NULL);
    }

    // ========================= Read the input file =========================
    int width = 0, height = 0; // the width and the height
    char line[100];
    char filename[] = "input";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(0);
    }

    fseek(file, 0, SEEK_SET); // to the start of the file
    int row = 0, col = 0;
    float temp = 0.;
    //read the the width and the height
    fgets(line, sizeof(line), file);
    sscanf(line, "%d %d", &width, &height);
    int sz = width * height;

    // ========================= Store the intial box to memory =========================
    float *init_box = malloc(sz * sizeof(float));
    for (size_t ix = 0; ix < width; ++ix)
    {
        for (size_t iy = 0; iy < height; ++iy)
        {
            init_box[ix * width + iy] = 0;
        }
    }
    //read the rest
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%d %d %f", &col, &row, &temp);
        init_box[row * width + col] = temp;
    }
    // close the file
    fclose(file);

    // ========================= OpenCL Initialization =========================
    cl_int error; // Used to handle error codes

    // ------ Platform ------
    cl_platform_id platform_id;
    cl_uint nmb_platforms;
    if (clGetPlatformIDs(1, &platform_id, &nmb_platforms) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot get platform\n");
        return 1;
    }

    // ------ Device ------
    cl_device_id device_id;
    cl_uint nmb_devices;
    if (clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &nmb_devices) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot get device\n");
        return 1;
    }

    // ------ Context ------
    cl_context context;
    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platform_id,
        0};
    context = clCreateContext(properties, 1, &device_id, NULL, NULL, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create context\n");
        return 1;
    }

    // ------ Command Queue ------
    cl_command_queue command_queue;
    command_queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create command queue\n");
        return 1;
    }

    // ------ Read Kernel Program from opencl file ------
    char *opencl_program_src;
    FILE *clfp = fopen("./diffusion.cl", "r");
    if (clfp == NULL)
    {
        fprintf(stderr, "could not load cl source code\n");
        return 1;
    }
    fseek(clfp, 0, SEEK_END);
    int clfsz = ftell(clfp);
    fseek(clfp, 0, SEEK_SET);
    opencl_program_src = (char *)malloc((clfsz + 1) * sizeof(char));
    fread(opencl_program_src, sizeof(char), clfsz, clfp);
    opencl_program_src[clfsz] = 0;
    fclose(clfp);

    // Create program from sourse
    cl_program program;
    size_t src_len = strlen(opencl_program_src);
    program = clCreateProgramWithSource(
        context, 1, (const char **)&opencl_program_src, (const size_t *)&src_len, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create program\n");
        return 1;
    }
    free(opencl_program_src);

    // Compile Program
    error = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot build program. log:\n");

        size_t log_size = 0;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        char *log = malloc(log_size * sizeof(char));
        if (log == NULL)
        {
            fprintf(stderr, "could not allocate memory\n");
            return 1;
        }

        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
        fprintf(stderr, "%s\n", log);
        free(log);
        return 1;
    }

    // ------ Create kernels ------
    // diffusion kernel
    cl_kernel kernel_diffuse_one_iter = clCreateKernel(program, "diffuse_one_iter", &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create kernel diffuse_one_iter\n");
        return 1;
    }
    // reduction sum kernel
    cl_kernel kernel_reduction_sum = clCreateKernel(program, "reduction_sum", &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create kernel reduce_sum\n");
        return 1;
    }
    // absolute difference kernel
    cl_kernel kernel_compute_abs_diff = clCreateKernel(program, "compute_abs_diff", &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create kernel compute_abs_diff\n");
        return 1;
    }

    // Create Buffers
    // two buffers are needed here, one for holding the box before one iteration, one for after
    cl_mem old_box, new_box;
    old_box = clCreateBuffer(context, CL_MEM_READ_WRITE, sz * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create buffer a\n");
        return 1;
    }

    new_box = clCreateBuffer(context, CL_MEM_READ_WRITE, sz * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create buffer b\n");
        return 1;
    }

    // Enqueue Buffer -- Give the initial box to old box
    if (clEnqueueWriteBuffer(command_queue, old_box, CL_TRUE, 0,
                             sz * sizeof(float), init_box, 0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue write of buffer a\n");
        return 1;
    }

    const size_t global_sz[] = {width, height}; // a global size, will be used both for calculate diffusion and abs diff
    // =========================================================== Diffuse iterations ===========================================================
    for (size_t iter = 0; iter < iter_num; ++iter)
    {
        // Set Kernels
        clSetKernelArg(kernel_diffuse_one_iter, 0, sizeof(cl_mem), &old_box);
        clSetKernelArg(kernel_diffuse_one_iter, 1, sizeof(cl_mem), &new_box);
        clSetKernelArg(kernel_diffuse_one_iter, 2, sizeof(float), &diff_const);
        clSetKernelArg(kernel_diffuse_one_iter, 3, sizeof(int), &width);
        clSetKernelArg(kernel_diffuse_one_iter, 4, sizeof(int), &height);

        // Two-Dimensional global args
        if (clEnqueueNDRangeKernel(command_queue, kernel_diffuse_one_iter,
                                   (cl_uint)2, NULL, (const size_t *)&global_sz, NULL, 0, NULL, NULL) != CL_SUCCESS)
        {
            fprintf(stderr, "cannot enqueue kernel_diffuse_one_iter\n");
            return 1;
        }

        if (clFinish(command_queue) != CL_SUCCESS)
        {
            fprintf(stderr, "cannot finish queue\n");
            return 1;
        }
        old_box = new_box;
    }

    // =========================================================== Compute average ===========================================================
    const int global_redsz = 1024;
    const int local_redsz = 32;
    const int nmb_redgps = global_redsz / local_redsz;

    // Buffer for reduced result
    cl_mem output_buffer_sum;
    output_buffer_sum = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                       nmb_redgps * sizeof(float), NULL, &error);
    if (error != CL_SUCCESS)
    {
        fprintf(stderr, "cannot create buffer output_buffer_sum\n");
        return 1;
    }

    const cl_int sz_clint = (cl_int)sz;
    clSetKernelArg(kernel_reduction_sum, 0, sizeof(cl_mem), &new_box);
    clSetKernelArg(kernel_reduction_sum, 1, local_redsz * sizeof(float), NULL);
    clSetKernelArg(kernel_reduction_sum, 2, sizeof(cl_int), &sz_clint);
    clSetKernelArg(kernel_reduction_sum, 3, sizeof(cl_mem), &output_buffer_sum);

    size_t global_redsz_szt = (size_t)global_redsz;
    size_t local_redsz_szt = (size_t)local_redsz;
    if (clEnqueueNDRangeKernel(command_queue,
                               kernel_reduction_sum, 1, NULL, (const size_t *)&global_redsz_szt, (const size_t *)&local_redsz_szt,
                               0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue kernel kernel_reduction_sum (sum)\n");
        return 1;
    }

    // Copy reduced sum to host
    float *reduced_output = malloc(nmb_redgps * sizeof(float));
    if (clEnqueueReadBuffer(command_queue,
                            output_buffer_sum, CL_TRUE, 0, nmb_redgps * sizeof(float), reduced_output, 0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue read of buffer reduced_output\n");
        return 1;
    }

    if (clFinish(command_queue) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot finish queue\n");
        return 1;
    }

    // Final reduction of averages on host
    float sum_total = 0;
    for (size_t ix = 0; ix < nmb_redgps; ++ix)
        sum_total += reduced_output[ix];

    //compute average temperature
    float average = sum_total / sz;

    printf("average: %f\n", average);

    // =========================================================== Compute abs diff ===========================================================
    clSetKernelArg(kernel_compute_abs_diff, 0, sizeof(cl_mem), &new_box);
    clSetKernelArg(kernel_compute_abs_diff, 1, sizeof(float), &average);
    clSetKernelArg(kernel_compute_abs_diff, 2, sizeof(int), &width);

    if (clEnqueueNDRangeKernel(command_queue, kernel_compute_abs_diff,
                               (cl_uint)2, NULL, (const size_t *)&global_sz, NULL, 0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue kernel_compute_abs_diff\n");
        return 1;
    }
    // =========================================================== Compute average abs diff ===========================================================
    if (clEnqueueNDRangeKernel(command_queue,
                               kernel_reduction_sum, 1, NULL, (const size_t *)&global_redsz_szt, (const size_t *)&local_redsz_szt,
                               0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue kernel kernel_reduction_sum (abs diff)\n");
        return 1;
    }
    // Copy reduced sum of abs diff to host
    float *reduced_output_diff = malloc(nmb_redgps * sizeof(float));
    if (clEnqueueReadBuffer(command_queue,
                            output_buffer_sum, CL_TRUE, 0, nmb_redgps * sizeof(float), reduced_output_diff, 0, NULL, NULL) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot enqueue read of buffer reduced_output\n");
        return 1;
    }

    if (clFinish(command_queue) != CL_SUCCESS)
    {
        fprintf(stderr, "cannot finish queue\n");
        return 1;
    }

    // Final reduction of averages on host
    float sum_diff_total = 0;
    for (size_t ix = 0; ix < nmb_redgps; ++ix)
        sum_diff_total += reduced_output_diff[ix];

    //compute average temperature
    float average_abs_diff = sum_diff_total / sz;

    printf("average absolute difference: %f\n", average_abs_diff);


    // Release Resources
    clReleaseMemObject(old_box);
    clReleaseMemObject(new_box);
    clReleaseMemObject(output_buffer_sum);
    clReleaseProgram(program);
    clReleaseKernel(kernel_diffuse_one_iter);
    clReleaseKernel(kernel_reduction_sum);

    clReleaseCommandQueue(command_queue);
    clReleaseContext(context);
    free(init_box);
    free(reduced_output);
    free(reduced_output_diff);
    return 0;
}