#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char** argv){

    if(argc != 2){
        return 1;
    }

    struct stat st;

    stat(argv[1], &st);
    printf("%ld\n",st.st_size);
    printf("%ld\n",st.st_dev);

    return 0;
}