__kernel void diffuse_one_iter(
    __global float *old_box, 
    __global float *new_box,
    const float diff_const, 
    const int width,
    const int height
    ) 
{
    int col = get_global_id(0);
    int row = get_global_id(1);

    int index = row * width + col;
    float h_ij = old_box[index];
    float left, right, up, down;
    left = (col - 1) >= 0 ? old_box[index - 1] : 0.;
    right = (col + 1) < width ? old_box[index + 1] : 0.;
    up = (row - 1) >= 0 ? old_box[index - width] : 0.;
    down = (row + 1) < height ? old_box[index + width] : 0.;
    new_box[index] = h_ij + diff_const * (0.25 * (left + right + up + down) - h_ij);
}

__kernel void reduction_sum(
    __global float *box,
    __local float *scratch,
    __const int sz,
    __global float* group_sums
    )
{
    int gsz = get_global_size(0);
    int gix = get_global_id(0);
    int lsz = get_local_size(0);
    int lix = get_local_id(0);
    
    float acc = 0;
    for (int tix = gix; tix < sz; tix+=gsz)
        acc += box[tix];

    scratch[lix] = acc;
    barrier(CLK_LOCAL_MEM_FENCE);

    for(int offset = lsz/2; offset>0; offset/=2) {
        if (lix < offset)
            scratch[lix] += scratch[lix+offset];
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    if (lix == 0)
        group_sums[get_group_id(0)] = scratch[0];
}

__kernel void compute_abs_diff(
    __global float * diff,
    const float average,
    const int width
    )
{
    int col = get_global_id(0);
    int row = get_global_id(1);

    diff[row * width + col] -= average;
    diff[row * width + col] = ( diff[row * width + col] < 0 ? diff[row * width + col]*-1.: diff[row * width + col] );
}