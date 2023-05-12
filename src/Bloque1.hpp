#include <string>
#include <vector>
using namespace std;

vector<unsigned char> StringHexToBytes(string hexString); // Codifica el string hexadecimal en bytes
string BytesToStringHex(vector<unsigned char> bytes); // Decodifica a string hexadecimal
string BytesToStringBase64(vector<unsigned char> bytes); // Decodifica los bytes en string base64

string StringHexToStringBase64(string hexString); // Bloque 1, Ejercicio 1
string XORBuffers(string buffer1, string buffer2); // Bloque 1, Ejercicio 2