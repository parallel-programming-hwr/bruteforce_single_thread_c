#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcrypt.h"
#include <inttypes.h>



#ifndef mycryptwrapper_
#define mycryptwrapper_


#define NEED_LIBGCRYPT_VERSION "1.6.5" //should be 1.8.5 but my libgcrypt as mismatched versions :(
#define algo GCRY_MD_SHA256
#define cipher GCRY_CIPHER_DES


void mycryptwrapper_init();

void mycryptwrapper_print();





#endif