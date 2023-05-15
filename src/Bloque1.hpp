#include <string>
#include <vector>
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

string StringHexToStringBase64(const string& hexString); // Bloque 1, Ejercicio 1
string XORBuffers(const string& in1, const string& in2); // Bloque 1, Ejercicio 2
char FindKey(const string& in); // Bloque 1, Ejercicio 3
string FindKeyFile(const string& nombreArchivo); // Bloque 1, Ejercicio 4
string RepeatingKeyXOR(const string& in, const string& key);// Bloque 1, Ejercicio 5
// Bloque 1, Ejercicio 7