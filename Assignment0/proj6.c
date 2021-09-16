#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int
main(
    int argc,
    char *argv[]
    )
{  
    
    char *a="a";
    char *b="b";

    for (int i=1; i<argc; i++)
    {
        // printf("%s\r\n",argv[i]);
        if(strstr(argv[i],a)){
            char* tmp_a = argv[i];
            char* a_num = &tmp_a[strlen(tmp_a)-1];
            
            printf("A is %d and ", atoi(a_num));
        }
        if(strstr(argv[i],b)) {
            char* tmp_b = argv[i];
            char* b_num = &tmp_b[strlen(tmp_b)-1];
            
            printf("B is %d\n", atoi(b_num));
        }

        // printf("A is %s and B is ",a_num);
            
    }

}  