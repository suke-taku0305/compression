#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>

int main(){

    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];

    //ランダムな鍵とIVを生成します。
    RAND_bytes(key, EVP_MAX_KEY_LENGTH);
    RAND_bytes(iv, EVP_MAX_IV_LENGTH);

    const char *plaintext = "This is a top secret message.";
    size_t plaintext_len = strlen(plaintext);

  // 暗号化するためのメモリを確保します。
    unsigned char ciphertext[plaintext_len + EVP_MAX_BLOCK_LENGTH];
    int ciphertext_len;

    EVP_CIPHER_CTX *ectx; 
    ectx = EVP_CIPHER_CTX_new();

    // AES-256-CBCを使用します。
    EVP_EncryptInit_ex(ectx, EVP_aes_256_cbc(), NULL, key, iv);

    // 暗号化を実行します。
    EVP_EncryptUpdate(ectx, ciphertext, &ciphertext_len, (const unsigned char*) plaintext, plaintext_len);

    // 最後のブロックを暗号化します。
    int len;
    EVP_EncryptFinal_ex(ectx, ciphertext + ciphertext_len, &len);
    ciphertext_len += len;

    // 暗号化されたデータを表示します。
    std::cout << "Ciphertext is: ";
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    std::cout << std::endl;

    EVP_CIPHER_CTX_free(ectx);

    return 0;
}
