#include <iostream>
#include <fstream>
#include "aes_function.h" // 前回のコードをaes_functions.hというファイルに保存したと仮定しています。

int main()
{
    std::ifstream ifs("./sample_text.txt");
    std::ofstream ofs;
    std::string data;
    std::string key = "ThisIsTheKey1234"; // AESキー
    std::string plaintext = "This is the plaintext message. I am testing for aes encryption. So I am trying to debug this code."; // 平文

    std::string buf;
    while(!ifs.eof()){
        std::getline(ifs, buf);
        data += buf + "\n";
    }

    // std::cout << data << std::endl;

    // 暗号化
    // std::string ciphertext = aes_function_encrypt(key, plaintext);
    std::string ciphertext = aes_function_encrypt(key, data);
    // std::cout << "Ciphertext: " << ciphertext << std::endl;
    ofs.open("./ciphertext.txt");
    ofs << ciphertext << std::endl;
    ofs.close();

    // 復号化
    std::string decrypted_text = aes_function_decrypt(key, ciphertext);
    // std::cout << "Decrypted text: " << decrypted_text << std::endl;
    ofs.open("./decrypted_text.txt");
    ofs << decrypted_text << std::endl;
    ofs.close();

    return 0;
}
