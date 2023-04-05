#include <openssl/aes.h>
#include <string>
#include <iostream>

std::string aes_function_encrypt(const std::string& key, const std::string& plaintext)
{
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE] = {0}; // 初期ベクトル
    std::string ciphertext;
    int len = 0;
    int ciphertext_len = 0;

    // AESキーの設定
    if (AES_set_encrypt_key((const unsigned char*)key.c_str(), key.length()*8, &aes_key) < 0) {
        std::cerr << "AES_set_encrypt_key() failed" << std::endl;
        return "";
    }

    // 暗号化
    len = plaintext.length();
    ciphertext.resize(len + AES_BLOCK_SIZE);
    AES_cbc_encrypt((const unsigned char*)plaintext.c_str(), (unsigned char*)ciphertext.c_str(), len, &aes_key, iv, AES_ENCRYPT);
    ciphertext_len = len + AES_BLOCK_SIZE;
    ciphertext.resize(ciphertext_len);
    
    return ciphertext;
}

std::string aes_function_decrypt(const std::string& key, const std::string& ciphertext)
{
    AES_KEY aes_key;
    unsigned char iv[AES_BLOCK_SIZE] = {0}; // 初期ベクトル
    std::string plaintext;
    int len = 0;

    // AESキーの設定
    if (AES_set_decrypt_key((const unsigned char*)key.c_str(), key.length()*8, &aes_key) < 0) {
        std::cerr << "AES_set_decrypt_key() failed" << std::endl;
        return "";
    }

    // 復号化
    len = ciphertext.length();
    plaintext.resize(len);
    AES_cbc_encrypt((const unsigned char*)ciphertext.c_str(), (unsigned char*)plaintext.c_str(), len, &aes_key, iv, AES_DECRYPT);
    plaintext.resize(len - AES_BLOCK_SIZE);

    return plaintext;
}
