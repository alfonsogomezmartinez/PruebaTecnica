#include "Bloque1.hpp"
#include <iostream>
#include <map>

vector<unsigned char> StringHexToBytes(const string& hexString){
    vector<unsigned char> bytes;

    // Convierte en bytes de base 16
    for (size_t i = 0; i < hexString.length(); i += 2) {
        unsigned char byte = static_cast<unsigned char>(stoi(hexString.substr(i, 2), nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

string BytesToStringHex(const vector<unsigned char>& bytes){
    string hexString;
    const string hexChars = "0123456789abcdef";

    for (const auto& byte : bytes) {
        hexString.push_back(hexChars[(byte >> 4) & 0x0F]);
        hexString.push_back(hexChars[byte & 0x0F]);
    }

    return hexString;
}

string BytesToStringBase64(const vector<unsigned char>& bytes){
    string base64String;
    const string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


    size_t padding = 3 - (bytes.size() % 3);
    if (padding == 3) padding = 0;
    for (size_t i = 0; i < bytes.size(); i += 3) {
        unsigned int combined = (bytes[i] << 16) | (bytes[i + 1] << 8) | bytes[i + 2];

        base64String.push_back(base64Chars[(combined >> 18) & 0x3F]);
        base64String.push_back(base64Chars[(combined >> 12) & 0x3F]);
        base64String.push_back(base64Chars[(combined >> 6) & 0x3F]);
        base64String.push_back(base64Chars[combined & 0x3F]);
    }
    base64String.resize(base64String.length() - padding, '=');


    return base64String;
}

string StringHexToStringBase64(const string& hexString) {
    vector<unsigned char> bytes = StringHexToBytes(hexString);
    string base64String = BytesToStringBase64(bytes);

    return base64String;
}

string XORBuffers(const string& in1, const string& in2, bool CS) {
    if (CS){
        try{
            if (in1.length() != in2.length()){
                string typeError = "Los parametros de entrada no tienen la misma longitud";
                throw typeError;
            }
        } catch (const string& typeError) {
            cout << "Error: " << typeError << endl;
        }
    }

    vector<unsigned char> aux;
    vector<unsigned char> buffer1 = StringHexToBytes(in1);
    vector<unsigned char> buffer2 = StringHexToBytes(in2);
    for (size_t i = 0; i < buffer1.size(); ++i) {
        unsigned char xorValue = buffer1[i] ^ buffer2[i];
        aux.push_back(xorValue);
    }
    string result = BytesToStringHex(aux);

    return result;
}

char findKey(const string& in) {
    string letterFrequency = "etaoin shrdlu";
    char key = 0;
    int maxScore = 0;
    vector<unsigned char> bytes = StringHexToBytes(in);

    for (int i = 0; i < 256; ++i) {
        string xoredBytes;

        for (const auto& byte : bytes) {
            unsigned char xoredByte = byte ^ i;
            xoredBytes.push_back(xoredByte);
        }

        // Calcular la puntuación para el resultado actual
        float score = 0.0;
        for (const auto& byte : xoredBytes) {
            char c = static_cast<char>(byte);

            // Verifica si el carácter está en la tabla de frecuencia de letras
            auto it = letterFrequency.find(tolower(c));
            if (it != -1)
                score ++;
        }

        // Actualiza la clave y la puntuación máxima si es necesario
        if (score > maxScore) {
            maxScore = score;
            key = static_cast<char>(i);
        }
    }

    return key;
}