#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void printName(char *fName){
    printf("%s: ",fName);
}

char* getOptions(){
    char *opt = malloc(10*sizeof(char));
    scanf("%s",opt);
    return opt;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Not good");
        return 1;
    }

    printName(argv[1]);
    char *opt = getOptions();

    printf("%s",opt);

    return 0;
}