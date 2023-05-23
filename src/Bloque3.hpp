#include "Bloque1.hpp"
#include "Bloque2.hpp"

string aes_ctr_encrypt(const string& key, vector<unsigned char> nonce, const string& input); // Cifrado AES 128 ctr
vector<vector<unsigned char>> transpose(const vector<std::vector<unsigned char>>& matrix); // transpuesto

string attack_ctr(const string& filename); // Bloque 3 Ejercicio 4