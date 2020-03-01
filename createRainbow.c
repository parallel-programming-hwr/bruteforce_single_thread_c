#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rainbowvalue.h"
#include "cryptwrapper.h"



int main(int argc, char const *argv[]) {
    if (argc != 2){
        printf("one argument expected ,argc =%i\n",argc);
        return 1;
    }
    FILE *fptr;
    fptr = fopen(argv[1],"r");
    if(fptr == NULL)
    {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }
    FILE *tfptr;
    char str[strlen(argv[1])+7];
    strcpy(str,argv[1]);
    strcat(str,".sha256");
    tfptr = fopen(str,"wb");
    if(tfptr == NULL)
    {
        printf("Could not create file %s\n", str);
        return 1;
    }
    mycryptwrapper_init();
    char line[256];

    gcry_error_t err;
    size_t mens = gcry_md_get_algo_dlen(algo);
    void * digest=malloc(mens);

    //printdata(buf,5);
    //printf("\n");
    struct s_rainbowvalue256 r;
    while (fgets(line, sizeof(line), fptr)) {
        gcry_md_hash_buffer(algo,digest,line,strlen(line)-1);// -1 so trailing \n is not used for calculation
        //mycryptwrapper_print(digest, strlen(digest));
        //printf("%s", line);
        strcpy(r.pw , line);
        strcpy(r.hash,digest);

        fwrite(&r, sizeof(struct s_rainbowvalue256),1,tfptr);
    }





    fclose(tfptr);
    fclose(fptr);
    return 0;
}