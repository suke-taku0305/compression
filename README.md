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

