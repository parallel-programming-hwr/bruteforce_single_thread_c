#include <stdio.h>
#include "gcrypt.h"
#include<stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <strings.h>


#include <inttypes.h>
#include "cryptwrapper.h"
#include "rainbowvalue.h"

#define NEED_LIBGCRYPT_VERSION "1.6.5" //should be 1.8.5 but my libgcrypt as mismatched versions :(
#define algo GCRY_MD_SHA256
#define cipher GCRY_CIPHER_DES

void printdata(const void * buf, size_t len){
    for (size_t i = 0; i< len; i++){
        printf("%x ", ((uint8_t*)buf)[i]);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2){
        printf("please select rainbow table\n");
        return 1;
    }
    FILE * fptr = fopen(argv[1],"rb");
    if (fptr==NULL){
        printf("could not open file %s\n",argv[1]);
        return 1;
    }
    char* pw_clear = malloc(256);
    memset(pw_clear,0,256);
    if (argc==3){
        strcpy(pw_clear,argv[2]);
    }
    else{
        strcpy(pw_clear,"ELEONORY");
    }
    const char * dummydata = "0123456789";
    mycryptwrapper_init();

    gcry_cipher_hd_t hd;
    gcry_error_t err= gcry_cipher_open(&hd,cipher,GCRY_CIPHER_MODE_CFB,0);

    size_t mens = gcry_md_get_algo_dlen(algo);
    void * digest=malloc(mens);

    gcry_md_hash_buffer(algo,digest,pw_clear,strlen(pw_clear));
    printf("hash Key:");
    mycryptwrapper_print(digest,mens);
    //printf("\n");
    if(gcry_cipher_setkey(hd,digest,8)){
        printf("could not set key for encryption");
    }
    size_t len = 8;
    void * iv = malloc(len);
    err = gcry_cipher_setiv(hd, iv , len);
    if (err){
        printf("could not init init vector");
    }
    unsigned char * encrypted_secret = malloc(32);

    err = gcry_cipher_encrypt(hd,encrypted_secret,32,dummydata,10);
    if (err){
        printf("could not encrypt");
    }
    printf("encypted data:");
    mycryptwrapper_print(encrypted_secret,32);
    //printf("\n");
    void  * out = malloc(256);//allocate mem for decrypted buffer
    struct s_rainbowvalue256 r;
    while (fread(&r, sizeof(struct s_rainbowvalue256), 1,fptr)) {//reading hash values from rainbowtable
        gcry_cipher_hd_t dhd;
        gcry_error_t err= gcry_cipher_open(&dhd,cipher,GCRY_CIPHER_MODE_CFB,0);
        if (err){
            printf("could not open handle\n");
        }
        //printf("hash key: ");
        //mycryptwrapper_print(r.hash,32);
        err = gcry_cipher_setkey(dhd,r.hash,8);
        if (err) {
            printf("could not set key \n");
        }
        memset(iv,0,len);
        err = gcry_cipher_setiv(dhd, iv , len);
        if (err){
            printf("could not init init vector");
        }


        memset(out,0,256);
        err = gcry_cipher_decrypt(dhd,out,256,encrypted_secret,strlen(encrypted_secret));
        if (err){
            printf("could not decrypt\n");
            }
        //printf("encrpyted secret:");
        //mycryptwrapper_print(encrypted_secret,strlen(encrypted_secret));

        //printf("\ndecrypted");
        //mycryptwrapper_print(out,256);
        if (strcmp(out,dummydata)==0){
            printf("pw: %sfor data: %s\npwhash: ", r.pw, (char*)out);
            mycryptwrapper_print(r.hash, strlen(r.hash));
            return 0;
        }
        gcry_cipher_close(dhd);//close cipher
    }
    printf("\nnothing found\n");

    //printdata(digest,mens);



    return 0;
}


