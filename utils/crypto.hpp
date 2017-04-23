#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/evp.h>

class bint;

bool enc_encrypt_cipher(bint& key,
                        bint& iv,
                        bint& input,
                        bint& output,
                        const EVP_CIPHER* cipher);

bool enc_decrypt_cipher(bint& key,
                        bint& iv,
                        bint& input,
                        bint& output,
                        const EVP_CIPHER* cipher);
#endif // CRYPTO_H
