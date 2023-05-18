#include <iostream>
#include <string>
#include <vector>
#include <openssl/rand.h>
#include <random>
using namespace std;

string aes_cbc_encrypt(const string& encrypted_data, const string& key, const string& IV); // Cifra aes 128 cbc
string aes_cbc_decrypt(const string& encrypted_data, const string& key, const string& IV); // Descifra con aes 128 cbc
string generateRandomKey(); // Generea una clave aleatoria de 16
string aes_ecb_encrypt(const string& plaintext, const string& key); // Encriptar texto con AES 128 ecb
bool detectBlockCipherMode(const std::string& ciphertext); // Detecta si se usa ECB

vector<uint8_t> pkcs7Padding(const std::string& input, size_t blockSize); // Bloque 2, Ejercicio 1
string FileEncryptAES128CBC(const string& fileName, const string& key, const string& iv); // Bloque 2, Ejercicio 2
pair<string, bool> fileTestB2E3(const string& filename); //BLoque 2 Ejercicio 3