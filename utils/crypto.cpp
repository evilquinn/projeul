
#include "crypto.hpp"
#include <bint.hpp>

#define BLOCK_SIZE_BYTES 8

bool enc_encrypt_cipher(
    bint& key,
    bint& iv,
    bint& input,
    bint& output,
    const EVP_CIPHER* cipher)
{
    EVP_CIPHER_CTX       encryption_context;
    EVP_CIPHER_CTX_init(&encryption_context);

    int success = 1;
    success &= EVP_EncryptInit_ex(&encryption_context,
                                  cipher,
                                  NULL,
                                  (unsigned char*)key,
                                  (unsigned char*)iv);
    //EVP_CIPHER_CTX_set_padding(&encryption_context, 0);

    // length of binary ciphertext is AT MOST =
    // plaintext_size + block_size - 1
    int ciphertext_length = input.size() + EVP_CIPHER_block_size(cipher);
    output = 0;
    output.resize(ciphertext_length);

    int bytes_written_op = 0;
    int bytes_written = 0;
    success &= EVP_EncryptUpdate(&encryption_context,
                                 (unsigned char*)output,
                                 &bytes_written_op,
                                 (const unsigned char*)input,
                                 input.size());
    bytes_written += bytes_written_op;

    success &= EVP_EncryptFinal_ex(&encryption_context,
                                   (unsigned char*)output + bytes_written,
                                   &bytes_written_op);
    bytes_written += bytes_written_op;
    output.resize_chararray(bytes_written);

    EVP_CIPHER_CTX_cleanup(&encryption_context);

    return success;
}

bool enc_decrypt_cipher(
    bint& key,
    bint& iv,
    bint& input,
    bint& output,
    const EVP_CIPHER* cipher)
{
    EVP_CIPHER_CTX       encryption_context;
    EVP_CIPHER_CTX_init(&encryption_context);

    int success = 1;
    success &= EVP_DecryptInit_ex(&encryption_context,
                                  cipher,
                                  NULL,
                                  (unsigned char*)key,
                                  (unsigned char*)iv);
    //EVP_CIPHER_CTX_set_padding(&encryption_context, 0);

    // length of binary ciphertext is AT MOST =
    // plaintext_size + block_size - 1
    int ciphertext_length = input.size() + EVP_CIPHER_block_size(cipher);
    output = 0;
    output.resize(ciphertext_length);

    int bytes_written_op = 0;
    int bytes_written = 0;
    success &= EVP_DecryptUpdate(&encryption_context,
                                 (unsigned char*)output,
                                 &bytes_written_op,
                                 (const unsigned char*)input,
                                 input.size());
    bytes_written += bytes_written_op;

    success &= EVP_DecryptFinal_ex(&encryption_context,
                                   (unsigned char*)output + bytes_written,
                                   &bytes_written_op);
    bytes_written += bytes_written_op;
    output.resize_chararray(bytes_written);

    EVP_CIPHER_CTX_cleanup(&encryption_context);

    return success;
}
