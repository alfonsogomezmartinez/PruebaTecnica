#include "Bloque1.hpp"

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

vector<unsigned char> XOR(const vector<unsigned char>& buffer1, const vector<unsigned char>& buffer2){
    vector<unsigned char> aux;

    for (size_t i = 0; i < buffer1.size(); ++i) {
        unsigned char xorValue = buffer1[i] ^ buffer2[i];
        aux.push_back(xorValue);
    }

    return aux;
}

string XORBuffers(const string& in1, const string& in2) {
    try{
        if (in1.length() != in2.length()){
            string typeError = "Los parametros de entrada no tienen la misma longitud";
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    vector<unsigned char> aux = XOR(StringHexToBytes(in1), StringHexToBytes(in2));

    string result = BytesToStringHex(aux);

    return result;
}

string XORCharacter(const vector<unsigned char>& bytes, int i){
    string xoredBytes;

    for (const auto& byte : bytes) {
        unsigned char xoredByte = byte ^ i;
        xoredBytes.push_back(xoredByte);
    }

    return xoredBytes;
}

int ScoreEnglish(const string& in){
    string letterFrequency = "etaoin shrdlu";
    int score = 0;

    for (const auto& byte : in) {
        char c = static_cast<char>(byte);

        // Verifica si el carácter está en la tabla de frecuencia de letras
        auto it = letterFrequency.find(tolower(c));
        if (it != -1)
            score ++;
    }

    return score;
}

char FindKey(const string& in) {
    char key = 0;
    int maxScore = 0;
    vector<unsigned char> bytes = StringHexToBytes(in);


    for (int i = 0; i < 256; ++i) {

        string xoredBytes = XORCharacter(bytes, i);

        // Calcular la puntuación para el resultado actual
        int score = ScoreEnglish(xoredBytes);

        // Actualiza la clave y la puntuación máxima si es necesario
        if (score > maxScore) {
            maxScore = score;
            key = static_cast<char>(i);
        }
    }

    return key;
}

string FindKeyFile(const string& fileName){
    ifstream file(fileName);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + fileName;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string key;
    string hexLine;
    int maxScore = 0;
    int score;

    while (getline(file, hexLine)) {
        vector<unsigned char> bytes = StringHexToBytes(hexLine);

        for (int i = 0; i < 256; ++i) {
            string aux = XORCharacter(bytes, i);
            score = ScoreEnglish(aux);
            if (score > maxScore) {
                maxScore = score;
                key = aux;
            }
        }
    }
    file.close();

    return key;
}

string RepeatingKeyXOR(const string& in, const string& key){
    vector<unsigned char> ciphertextBytes;
    unsigned char encryptedByte;

    for (int i = 0; i < in.length(); ++i) {
        encryptedByte =  in[i] ^ key[i % key.length()];
        ciphertextBytes.push_back(encryptedByte);
    }

    return BytesToStringHex(ciphertextBytes);
}

string base64_decode(const string& encoded_string) {
    BIO* bio = BIO_new(BIO_f_base64());
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(encoded_string.data(), encoded_string.length());
    bmem = BIO_push(bio, bmem);

    char buffer[1024];
    string decoded_string;

    while (true) {
        int bytes_read = BIO_read(bmem, buffer, sizeof(buffer));
        if (bytes_read > 0)
            decoded_string.append(buffer, bytes_read);
        else
            break;
    }

    BIO_free_all(bmem);

    return decoded_string;
}

string aes_ecb_decrypt(const string& encrypted_data, const string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, (const unsigned char*)key.c_str(), nullptr);

    int decrypted_length = 0;
    int total_decrypted_length = 0;
    string decrypted_data(encrypted_data.size() + AES_BLOCK_SIZE, '\0');

    EVP_DecryptUpdate(ctx, (unsigned char*)decrypted_data.data(), &decrypted_length, (const unsigned char*)encrypted_data.data(), encrypted_data.size());
    total_decrypted_length += decrypted_length;

    EVP_DecryptFinal_ex(ctx, (unsigned char*)decrypted_data.data() + total_decrypted_length, &decrypted_length);
    total_decrypted_length += decrypted_length;

    EVP_CIPHER_CTX_free(ctx);
    decrypted_data.resize(total_decrypted_length);

    return decrypted_data;
}

string base64FileDecryptAES128ECB(const string& fileName, const string& key){
    ifstream file(fileName);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + fileName;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string hexLine, base64_encoded_data;

    while (getline(file, hexLine)) {
        base64_encoded_data.append(hexLine);
    }

    string decoded_data = base64_decode(base64_encoded_data);
    string decrypted_data = aes_ecb_decrypt(decoded_data, key);

    return decrypted_data;
}

bool compareFile(const string& filename1, const string& filename2) {
    ifstream file1(filename1);
    ifstream file2(filename2);
    string datafile1, datafile2;

    if (file1.is_open() && file2.is_open()) {
        getline(file1, datafile1, '\0');
        getline(file2, datafile2, '\0');
        file1.close();
        file2.close();

        return datafile1 == datafile2;
    }

    return false;
}

pair<int, int> detectECBBlock(const string& ciphertext) {
    // Divide el texto cifrado en bloques de 16 bytes
    int numBlocks = ciphertext.length() / 16;

    // Verifica si hay bloques idénticos en el texto cifrado
    for (int i = 0; i < numBlocks - 1; ++i) {
        string block1 = ciphertext.substr(i * 16, 16);
        for (int j = i + 1; j < numBlocks; ++j) {
            string block2 = ciphertext.substr(j * 16, 16);
            if (block1 == block2)
                return make_pair(i, j); // Se encontraron bloques idénticos, probablemente se usa el modo ECB
        }
    }

    return make_pair(-1, -1);  // No se encontraron bloques idénticos, probablemente se usa el modo CBC
}

pair<int, int> analyseFileDtectECBBlock(const string& fileName){
    ifstream file(fileName);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + fileName;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string hexLine, hex_encoded_data;

    while (getline(file, hexLine))
        hex_encoded_data.append(hexLine);

    vector<unsigned char> bytes = StringHexToBytes(hex_encoded_data);
    string decoded_data = string(bytes.begin(), bytes.end());

    return detectECBBlock(decoded_data);
}