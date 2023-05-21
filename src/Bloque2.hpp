#include <iostream>
#include <string>
#include <vector>
#include <openssl/rand.h>
#include <random>
#define GLOBALKEY "YELLOW SUBMARINE"
#include <map>
using namespace std;

string aes_cbc_encrypt(const string& encrypted_data, const string& key, const string& IV); // Cifra aes 128 cbc
string aes_cbc_decrypt(const string& encrypted_data, const string& key, const string& IV); // Descifra con aes 128 cbc
string generateRandomKey(); // Generea una clave aleatoria de 16
string aes_ecb_encrypt(const string& plaintext, const string& key); // Encriptar texto con AES 128 ecb
bool detectBlockCipherMode(const string& ciphertext); // Detecta si se usa ECB
map<string, string> parsingRoutine(const string& input); // Rutina de analisis
int getBlockSize(const string& filename, const string& key); // TAmamño del bloque en bytes
string profileFor(const string& email); // Encripta el correo

vector<uint8_t> pkcs7Padding(const std::string& input, size_t blockSize); // Bloque 2, Ejercicio 1
string FileEncryptAES128CBC(const string& fileName, const string& key, const string& iv); // Bloque 2, Ejercicio 2
pair<string, bool> fileTestB2E3(const string& filename); //Bloque 2 Ejercicio 3
string createAdminProfile(const string& email); //Bloque 2 Ejercicio 5