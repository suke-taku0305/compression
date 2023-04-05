#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdint>
#include <vector>
#include <type_traits>
#include <array>
#include <cstddef>
#include <filesystem>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <openssl/evp.h>
#include <type_traits>
#include <cstddef>
using byte = uint8_t;
using byte_stream = std::vector<byte>;
template < 
    size_t key_size,
    std::enable_if_t<key_size == 128 || key_size == 192 || key_size == 256, std::nullptr_t> = nullptr
>
using key = std::array<byte, key_size / 8>
const auto BLOCK_SIZE = 16;
using iv = std::array<byte, BLOCK_SIZE>;

template <
    size_t key_size,
    std::enable_if_t<key_size == 128 || key_size == 192 || key_size == 256, std::nullptr_t> = nullptr
>

auto
encrypt(
    const key<key_size>& key,
    const byte_stream& data,
    const iv& iv
) -> byte_stream {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr){
        throw "cannot initialize OpenSSL cipher context";
    }
    const EVP_CIPHER* cipher_suite;
    switch(key_size) {
        case 128:
            cipher_suite = EVP_aes_128_cbc();
            break;
        case 192:
            cipher_suite = EVP_aes_192_cbc();
            break;
        case 256:
            cipher_suite = EVP_aes_256_cbc();
            break;
    }

    if(cipher_suite == nullptr){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot get cipher suite";
    }
    if(EVP_EncryptInit(ctx, cipher_suite, key.data(), iv.data()) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot construct OpenSSL cipher context";
    }

    auto encrypted_data = byte_stream(
        raw_data.size() + (BLOCK_SIZE - raw_data.size() % BLOCK_SIZE)
    );
    int len = 0;
    if(EVP_EncryptUpdate(ctx, encrypted_data.data(), &len, data.data(), raw_data.size()) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot encrypt data";
    }

    if(EVP_EncryptFinal(ctx, encrypted_data.dataA() + len, &len) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot padding";
    }

    EVP_CIPHER_CTX_free(ctx);
    return encrypted_data;
}

template <
    size_t key_size,
    std::enable_if_t<key_size == 128 || key_size == 192 || key_size == 256, std::nullptr_t> = nullptr
>

auto 
decrypt(
    const key<key_size>& key,
    const byte_stream& data,
    const iv& iv
) -> byte_stream{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if(ctx == nullptr){
        throw "cannot initialize OpenSSL cipher context";
    }
    const EVP_CIPHER* cipher_suite;
    switch(key_size){
        case 128:
            cipher_suite = EVP_aes_128_cbc();
            break;
        case 192:
            cipher_suite = EVP_aes_192_cbc();
            break;
        case 256:
            cipher_suite = EVP_aes_256_cbc();
            break;
    }
    if(cipher_suite == nullptr){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot get cipher suite";
    }
    if(EVP_DecryptInit(ctx, cipher_suite, key.data(), iv.data()) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot construct OpenSSL cipher context";
    }

    auto plain_data = byte_stream(encrypted_data.size());
    int plain_data_len = 0;
    if(EVP_DecryptUpdate(ctx, plain_data.data(), &plain_data_len, encrypted_data.data(), encrypted_data.size()) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot encrypt data";
    }

    int remain_plain_data_len;
    if(EVP_DecryptFinal(ctx, plain_data.data() + plain_data_len, &remain_plain_data_len) == 0){
        EVP_CIPHER_CTX_cleanup(ctx);
        throw "cannot padding";
    }

    plain_data.resize(plain_data_len + remain_plain_data_len);
    EVP_CIPHER_CTX_free(ctx);
    return plain_data;
}

template <
    size_t key_size,
    std::enable_if_t<key_size == 128 || key_size == 192 || key_size == 256, std::nullptr_t> = nullptr
>

auto
print_data_while_encoding(
    const byte_stream& original_key,
    const byte_stream& data,
    const byte_stream& original_iv,
    const std::function<byte_stream(const key<key_size>&, const byte_stream&, const iv&)>& encoder
) -> void {
    iv iv;
    key<key_size> key;
    if(iv.size() != original_iv.size()){
        throw std::invalid_argument("iv length must be 128 bit");
    }
    if(original_key.size() != key.size()){
        throw std::invalid_argument("invalid key size");
    }
    std::copy(original_iv.begin(), original_iv.end(), iv.begin());
    std::copy(original_key.begin(), original_key.end(), key.begin());

    auto encoded_data = encoder(key, data, iv);
    for(const auto byte_value : encoded_data) {
        std::cout << byte_value;
    }
}

auto
convert_hex_string(const std::string& hex_string){
    if(hex_string.size() % 2 != 0){
        throw std::invalid_argument("invalid hex string");
    }

    byte_stream byte_array(hex_string.size() / 2);
    for(std::size_t i = 0; i < hex_string.size(); i += 2){
        auto&& byte_value = static_cast<uint8_t>(
            std::stoi(hex_string.substr(i, 2), nullptr, 16)
        );
        byte_array[i / 2] = byte_value;
    }

    return byte_array;
}

int
main(int argc, char* argv[]){
    const auto program_path = argv[0];
    byte_stream iv(BLOCK_SIZE, 0);
    byte_stream key(128 / 8, 0);
    int opt;
    while ((opt = getopt(argc, argv, "hi:k:V")) != -1) {
        switch (opt) {
            case 'h':
                usage(program_path);
                return 0;
            case 'i':
                try {
                    iv = convert_hex_string(optarg);
                } catch (const std::invalid_argument& error){
                    std::cerr << "invalid iv format" << std::endl;
                    return 1;
                } catch (const std::out_of_range& error){
                    std::cerr << error.what() << std::endl;
                    return 1;
                }
                if(iv.size() != BLOCK_SIZE){
                    std::cerr << "iv must be 128 bit" << std::endl;
                }
                break;
            case 'k':
                try{
                    key = convert_hex_string(optarg);
                }catch (const std::invalid_argument& error){
                    std::cout << "invalid key format" << std::endl;
                    return 1;
                }catch (const std::out_of_range& error){
                    std::cerr << error.what() << std::endl;
                    return 1;
                }
                if(!(key.size() == 128 / 8 || key.size() == 192/8 || key.size() == 256 / 8)){
                    std::cerr << "key size must be 128, 192 or 256 bit" << std::endl;
                }
                break;
            default:
                return 1;
        }
    }
    if(argc - optind < 1){
        std::cerr << "no subcommand" << std::endl;
        return 1;
    }
    auto subcommand = std::string(argv[optind]);
    if(subcommand == "help") {
        usage(program_path);
        return 0;
    }
    if(subcommand == "enc"){
        switch(key.size() * 8){
            case 128:
                print_data_while_encoding<128>(key, data, iv, encrypt<128>);
                break;
            case 192:
                print_data_while_encoding<192>(key, data, iv, encrypt<192>);
                break;
            case 256:
                print_data_while_encoding<256>(key, data, iv, encrypt<256>);
                break;
            default:
                std::cout << "invalid key type" << std::endl;
                return 1;
        }
    }else if (subcommand == "dec"){
        switch(key.size() * 8){
            case 128:
                print_data_while_encoding<128>(key, data, iv, encrypt<128>);
                break;
            case 192:
                print_data_while_encoding<192>(key, data, iv, encrypt<192>);
                break;
            case 256:
                print_data_while_encoding<256>(key, data, iv, encrypt<256>);
                break;
            default:
                std::cout << "invalid key type" << std::endl;
                return 1;
    } else {
        std::cerr << "unknown command: " << subcommand << std::endl;
        return 1;
    }

    auto
    usage(const std::filesystem::path& program_path) -> void {
        const auto program_name = program_path.filename().generic_string();

        std::cout 
        << "OpenSSLライブラリの使用方法のサンプル" << std::endl
        << "Usage:"  << std::endl
        << "  " << program_name << " enc" << std::endl
        << "  " << program_name << " dec" << std::endl
        << "  " << program_name << " help" << std::endl
        << "  " << program_name << " -h" << std::endl
        << "Arguments:" << std::endl
        << "  enc" << std::endl
        << "    標準入力から受け取ったデータを暗号化し，" << std::endl
        << "    標準出力へ出力する" << std::endl
        << "  dec" << std::endl
        << "    標準入力から受け取ったデータを復号化し，" << std::endl
        << "    標準出力へ出力する" << std::endl
        << "  help" << std::endl
        << "    ヘルプを表示する" << std::endl
        << "Options:" << std::endl
        << "  -h" << std::endl
        << "    ヘルプを表示する" << std::endl
        << "  -i <iv>"                                    << std::endl
        << "    <iv>で指定された値でIVを作成する。"       << std::endl
        << "    <iv>はHex String形式(例: AB01DF93BC)で"   << std::endl
        << "    長さが128bitになるようにする必要がある"   << std::endl
        << "  -k <key>"                                   << std::endl
        << "    <key>で指定された値で鍵を作成する。"      << std::endl
        << "    <key>はhex String形式で長さが128 bit,"    << std::endl
        << "    192 bit, 256 bitのいずれかの"             << std::endl
        << "    長さになる必要がある。"                   << std::endl;
    }

    byte_stream data;
    while(true){
        auto byte_value = getc(stdin);
        if(byte_value == EOF) {
            break;
        }
        data.emplace_back(byte_value);
    }
}
