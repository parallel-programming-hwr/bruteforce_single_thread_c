#include "cryptwrapper.h"

void mycryptwrapper_init(){

    /* Version check should be the very first call because it
    makes sure that important subsystems are initialized.
    #define NEED_LIBGCRYPT_VERSION to the minimum required version. */
    if (!gcry_check_version (NEED_LIBGCRYPT_VERSION))
    {
        fprintf (stderr, "libgcrypt is too old (need %s, have %s)\n",
                 NEED_LIBGCRYPT_VERSION, gcry_check_version (NULL));
        exit (2);
    }

    /* Disable secure memory.  */
    gcry_control (GCRYCTL_DISABLE_SECMEM, 0);

    /* ... If required, other initialization goes here.  */

    /* Tell Libgcrypt that initialization has completed. */
    gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

}

void  mycryptwrapper_print(const void * buf, size_t len){
    for (size_t i = 0; i< len; i++){
        printf("%02x ", ((uint8_t*)buf)[i]);
    }
    printf("\n");
}

