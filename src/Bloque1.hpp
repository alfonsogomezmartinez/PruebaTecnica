#include <string>
#include <vector>
using namespace std;

vector<unsigned char> StringHexToBytes(const string& hexString); // Codifica el string hexadecimal en bytes
string BytesToStringHex(const vector<unsigned char>& bytes); // Decodifica a string hexadecimal
string BytesToStringBase64(const vector<unsigned char>& bytes); // Decodifica los bytes en string base64

string StringHexToStringBase64(const string& hexString); // Bloque 1, Ejercicio 1
string XORBuffers(const string& in1, const string& in2, bool CS = true); // Bloque 1, Ejercicio 2
char findKey(const string& in); // Bloque 1, Ejercicio 3