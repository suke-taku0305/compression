#include <iostream>
#include <string>
using namespace std;

int main() {
    std::string originalString = "Hello, ASCII!"; // 変換したい元の文字列

    // 文字列をASCIIコードの列に変換
    std::string asciiCodeString = "";
    for (char c : originalString) {
        asciiCodeString += std::to_string(static_cast<int>(c)) + " ";
    }

    std::cout << "ASCIIコードの列: " << asciiCodeString << std::endl;

    // ASCIIコードの列を元の文字列に戻す
    std::string decodedString = "";
    std::string currentAsciiCode = "";

    for (char c : asciiCodeString) {
        if (c != ' ') {
            currentAsciiCode += c;
        } else {
            int asciiValue = std::stoi(currentAsciiCode);
            decodedString += static_cast<char>(asciiValue);
            currentAsciiCode = "";
        }
    }

    std::cout << "元の文字列: " << decodedString << std::endl;

    return 0;
}
