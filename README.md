# compression
compression code for study

This is repository for studying compression and encryption.

tips for compiling the codes and usage

## aes/aes_main.cpp
```
g++ -o aes_main aes_main.cpp -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto
```
or
```
g++ -o aes_main aes_main.cpp aes_function.cpp -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto
```

## huffman/huffman.cpp

```
g++ -std=c++17 -o huffman huffman.cpp
```

## encomp
how to make dumped and undumped file

### make dumped file
```
cat ciphertext.txt | hexdump -Cv > dumped.txt
```
### you can zip compression for dumped.txt
```
zip dumped.zip dumped.txt
```

### undumped
```
cat dumped.txt | xxd -r -p > undumped.txt
```

then you can decryption using undumped.txt
