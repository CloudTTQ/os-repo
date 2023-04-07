#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

void printName(char *fName){
    printf("%s: ",fName);
}

char* getOptions(){
    char *opt = malloc(10*sizeof(char));
    scanf("%s",opt);
    return opt;
}

void compareForRights(int mask, int rights){
    //printf("%d\n%d",mask,rights);
    if(mask&rights){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
}

void printAccessRights(int rights){
    int mask = 0b100000000;
    int shifts = 0;

    printf("AccessRights: \n");
    while(shifts < 9){
        switch (shifts)
        {
        case 0:
            printf("Owner:\n    Read: ");
            compareForRights(mask,rights);
            break;
        case 1:
            printf("    Write: ");
            compareForRights(mask,rights); 
            break;
        case 2:
            printf("    Exec: ");
            compareForRights(mask,rights);
            break;
        case 3:
            printf("Group:\n    Read: ");
            compareForRights(mask,rights);
            break;
        case 4:
            printf("    Write: ");
            compareForRights(mask,rights);
            break;
        case 5:
            printf("    Exec: ");
            compareForRights(mask,rights);
            break;
        case 6:
            printf("Other:\n    Read: ");
            compareForRights(mask,rights);
            break;
        case 7:
            printf("    Write: ");
            compareForRights(mask,rights);
            break;
        case 8:
            printf("    Exec: ");
            compareForRights(mask,rights);
            break;
        
        default:
            break;
        }
        mask = mask>>1;
        shifts++;
    }
}

void createSymLink(char *fName){
    char symName[20];
    printf("Enter name for the symlink file: ");
    scanf("%s",symName);
    //printf("%s",symName);

    if(!symlink(fName,symName)){
        printf("Symlink created successfuly!\n");
    }

}

void menuRegFile(char *fName){
    char *opt = getOptions();
    struct stat st;
    stat(fName, &st);

    //printf("%s\n",opt);

    for(int i=1; i<strlen(opt); i++){
        //printf("%c\n", opt[i]);

        switch (opt[i])
        {
        case 'n':
            printf("Name: %s\n",fName);
            break;

        case 'd':
            printf("Size: %ld\n",st.st_size);
            break;

        case 'h':
            printf("HardLinkCount: %ld\n",st.st_nlink);
            break;

        case 'm':
            printf("LastModified: %ld\n",st.st_mtime);
            break;
        
        case 'a':
            printAccessRights(st.st_mode);
            break;

        case 'l':
            createSymLink(fName);
            break;

        default:
            printf("Wrong input, %c does not exist!",opt[i]);
        }
    }
}

void menuSymLink(char* fName){
    char *opt = getOptions();
    struct stat st;
    stat(fName, &st);

    for(int i=1; i<strlen(opt); i++){
        //printf("%c\n", opt[i]);

        switch (opt[i])
        {
        case 'n':
            printf("Name: %s\n",fName);
            break;

        case 'd':
            printf("Size: %ld\n",st.st_size);
            break;

        case 'l':
            unlink(fName);
            break;
        
        case 'a':
            printAccessRights(st.st_mode);
            break;

        default:
            printf("Wrong input, %c does not exist!",opt[i]);
        }
    }
}

void menuDir(char* fName){
    char *opt = getOptions();
    struct stat st;
    stat(fName, &st);

    for(int i=1; i<strlen(opt); i++){
        //printf("%c\n", opt[i]);

        switch (opt[i])
        {
        case 'n':
            printf("Name: %s\n",fName);
            break;

        case 'd':
            printf("Size: %ld\n",st.st_size);
            break;
        
        case 'a':
            printAccessRights(st.st_mode);
            break;

        case 'c':
            //how many .c files inside?
            break;

        default:
            printf("Wrong input, %c does not exist!",opt[i]);
        }
    }
}

int main(int argc, char** argv){
    if(argc == 1){
        printf("Not good");
        return 1;
    }

    struct stat st;

    for(int i=1; i< argc; i++){

    stat(argv[i],&st);
    printName(argv[i]);
    switch (st.st_mode & __S_IFMT)
    {
    case __S_IFREG:
        printf("Regular\n");
        menuRegFile(argv[i]);
        break;

    case __S_IFLNK:
        printf("SymLink\n");
        menuSymLink(argv[i]);
        break;

    case __S_IFDIR:
        printf("Directory\n");
        menuDir(argv[i]);
        break;
    
    default:
    printf("Filetype not supported!\n");
        break;
    }
    }

    return 0;
}