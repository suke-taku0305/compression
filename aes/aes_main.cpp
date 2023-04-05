#include <iostream>
#include "aes_function.h" // 前回のコードをaes_functions.hというファイルに保存したと仮定しています。

int main()
{
    std::string key = "ThisIsTheKey1234"; // AESキー
    std::string plaintext = "This is the plaintext message. I am testing for aes encryption. So I am trying to debug this code."; // 平文

    // 暗号化
    std::string ciphertext = aes_function_encrypt(key, plaintext);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    // 復号化
    std::string decrypted_text = aes_function_decrypt(key, ciphertext);
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}
