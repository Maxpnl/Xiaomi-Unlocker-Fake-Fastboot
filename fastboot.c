#include <unistd.h>
#include <stdio.h>


void printFileContents(char* filename){
    int c;
    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}

void writeToLog(int argc, char *argv[]){
   FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("LOG.txt","a");

    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }

    for(int i = 1; i < argc; i++)
    {
        fprintf(fptr, "%s\n", argv[i]);
    }

    fclose(fptr);
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc == 2 && strcmp(argv[1], "devices") == 0 ){
        printFileContents("devices.txt");
    } else if (argc >= 5 && strcmp(argv[1], "oem") == 0){
        if (strcmp(argv[2], "device-info") == 0) {
            printFileContents("oem device-info.txt");
        } else if (strcmp(argv[2], "lks") == 0) {
            printFileContents("oem lks.txt");
        }
            else {
        sleep(130);

        writeToLog(argc, argv);
    }
    } else if (argc >= 3 && strcmp(argv[1], "getvar") == 0){
        if (strcmp(argv[2], "token") == 0){
            printFileContents("get_token.txt");
        }
        else if (strcmp(argv[2], "product") == 0){
            printFileContents("get_product.txt");
        }
        else if (strcmp(argv[2], "tokenversion") == 0){
            printFileContents("get_token_version_err.txt");
        }
            else {
        sleep(130);

        writeToLog(argc, argv);
    }
          
    }
    else {
        sleep(130);
        writeToLog(argc, argv);
    }
}


