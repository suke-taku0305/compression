#include <iostream>
#include <cstring>
#include <openssl/aes.h>

const int KEY_SIZE = 32;
const int IV_SIZE = 16;
const int BLOCK_SIZE = 16;

void encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY aes_key;
    //AES_init_key(key, KEY_SIZE * 8, &aes_key);
    AES_set_encrypt_key(key, KEY_SIZE * 8, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
}

void decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, KEY_SIZE * 8, &aes_key);
    // AES_cbc_decrypt(ciphertext, plaintext, ciphertext_len, &aes_key, iv, AES_DECRYPT);
     AES_decrypt(ciphertext, plaintext, &aes_key);
}

int main() {
    unsigned char key[KEY_SIZE];
    unsigned char iv[IV_SIZE];
    unsigned char *plaintext;
    unsigned char *ciphertext;
    unsigned char *decryptedtext;

    std::string input_string = "Hello World! This is plain text for aes test";
    int input_length = input_string.length();

    plaintext = new unsigned char[input_length + BLOCK_SIZE];
    std::memcpy(plaintext, input_string.c_str(), input_length);
    std::memset(plaintext + input_length, 0, BLOCK_SIZE - (input_length % BLOCK_SIZE));

    ciphertext = new unsigned char[input_length + BLOCK_SIZE];
    decryptedtext = new unsigned char[input_length + BLOCK_SIZE];

    // Set key and iv
    std::memset(key, 0x00, KEY_SIZE);
    std::memset(iv, 0x00, IV_SIZE);

    // Encrypt plaintext
    encrypt(plaintext, input_length + BLOCK_SIZE, key, iv, ciphertext);

    // Print ciphertext
    std::cout << "Ciphertext: ";
    for (int i = 0; i < input_length + BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    std::cout << std::endl;

    // Decrypt ciphertext
    decrypt(ciphertext, input_length + BLOCK_SIZE, key, iv, decryptedtext);

    // Print decrypted text
    std::cout << "Decrypted text: " << decryptedtext << std::endl;

    delete[] plaintext;
    delete[] ciphertext;
    delete[] decryptedtext;

    return 0;
}
