#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
using namespace std;

vector<unsigned char> StringHexToBytes(const string& hexString); // Codifica el string hexadecimal en bytes
string BytesToStringHex(const vector<unsigned char>& bytes); // Decodifica a string hexadecimal
string BytesToStringBase64(const vector<unsigned char>& bytes); // Decodifica los bytes en string base64
string XORCharacter(const vector<unsigned char>& bytes, int i); // XOR un caracter
int ScoreEnglish(const string& in); // Calcular la puntuación para el resultado
vector<unsigned char> XOR(const vector<unsigned char>& buffer1, const vector<unsigned char>& buffer2); // XOR basico
string base64_decode(const string& encoded_string);
string aes_ecb_decrypt(const string& encrypted_data, const string& key); // Decript aes 128 ecb
pair<int, int> detectECBBlock(const string& ciphertext); // Detecta la posicion de los bloques

string StringHexToStringBase64(const string& hexString); // Bloque 1, Ejercicio 1
string XORBuffers(const string& in1, const string& in2); // Bloque 1, Ejercicio 2
char FindKey(const string& in); // Bloque 1, Ejercicio 3
string FindKeyFile(const string& nombreArchivo); // Bloque 1, Ejercicio 4
string RepeatingKeyXOR(const string& in, const string& key);// Bloque 1, Ejercicio 5
string base64FileDecryptAES128ECB(const string& fileName, const string& key); // Bloque 1, Ejercicio 7
bool compareFile(const string& nombreArchivo1, const string& nombreArchivo2); // Bloque 1, Ejercicio 7
pair<int, int> analyseFileDtectECBBlock(const string& fileName); // Bloque 1 Ejercicio 8