#include <iostream>
#include <string>
#include <vector>
using namespace std;

string aes_cbc_encrypt(const string& encrypted_data, const string& key, const string& IV); // Cifra aes 128 cbc
string aes_cbc_decrypt(const string& encrypted_data, const string& key, const string& IV); // Descifra con aes 128 cbc

vector<uint8_t> pkcs7Padding(const std::string& input, size_t blockSize); // Bloque 2, Ejercicio 1
string FileEncryptAES128CBC(const string& fileName, const string& key, const string& iv); // Bloque 2, Ejercicio 2