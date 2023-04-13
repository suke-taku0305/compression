#ifndef AES_FUNCTION_H
#define AES_FUNCTION_H

#include <string>

// aes_functions.cppをインクルードする
#include "aes_function.cpp"

std::string aes_function_encrypt(const std::string& key, const std::string& plaintext);
std::string aes_function_decrypt(const std::string& key, const std::string& ciphertext);

#endif
