#include "Bloque1.hpp"
#include "Bloque2.hpp"

vector<uint8_t> pkcs7Padding(const string& input, size_t blockSize) {
    vector<uint8_t> paddedBlock;
    size_t inputSize = input.size();
    size_t paddingSize = blockSize - (inputSize % blockSize);

    // Copia de la entrada
    paddedBlock.insert(paddedBlock.end(), input.begin(), input.end());

    // Añade los bytes de padding
    for (size_t i = 0; i < paddingSize; i++) {
        paddedBlock.push_back(static_cast<uint8_t>(paddingSize));
    }

    return paddedBlock;
}

string aes_cbc_encrypt(const string& plain_data, const string& key, const string& IV) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, (const unsigned char*)key.c_str(), (const unsigned char*)IV.c_str());

    int encrypted_length = 0;
    int total_encrypted_length = 0;
    string encrypted_data(plain_data.size() + AES_BLOCK_SIZE, '\0');

    EVP_EncryptUpdate(ctx, (unsigned char*)encrypted_data.data(), &encrypted_length, (const unsigned char*)plain_data.data(), plain_data.size());
    total_encrypted_length += encrypted_length;

    EVP_EncryptFinal_ex(ctx, (unsigned char*)encrypted_data.data() + total_encrypted_length, &encrypted_length);
    total_encrypted_length += encrypted_length;

    EVP_CIPHER_CTX_free(ctx);
    encrypted_data.resize(total_encrypted_length);

    return encrypted_data;
}

string aes_cbc_decrypt(const string& encrypted_data, const string& key, const string& IV) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, (const unsigned char*)key.c_str(), (const unsigned char*)IV.c_str());

    int decrypted_length = 0;
    int total_decrypted_length = 0;
    string decrypted_data(encrypted_data.size(), '\0');

    EVP_DecryptUpdate(ctx, (unsigned char*)decrypted_data.data(), &decrypted_length, (const unsigned char*)encrypted_data.data(), encrypted_data.size());
    total_decrypted_length += decrypted_length;

    EVP_DecryptFinal_ex(ctx, (unsigned char*)decrypted_data.data() + total_decrypted_length, &decrypted_length);
    total_decrypted_length += decrypted_length;

    EVP_CIPHER_CTX_free(ctx);
    decrypted_data.resize(total_decrypted_length);

    return decrypted_data;
}

string FileEncryptAES128CBC(const string& fileName, const string& key, const string& iv){
    ifstream file(fileName);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + fileName;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string hexLine, data;

    while (getline(file, hexLine))
        data.append(hexLine+"\n");

    string crypted_data = aes_cbc_encrypt(data, key, iv);

    return crypted_data;
}

string aes_ecb_encrypt(const string& plaintext, const string& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, (unsigned char*)key.c_str(), nullptr);

    int encrypted_length = 0;
    int total_encrypted_length = 0;
    string encrypted_data(plaintext.size() + AES_BLOCK_SIZE, '\0');

    EVP_EncryptUpdate(ctx, (unsigned char*)encrypted_data.data(), &encrypted_length, (unsigned char*)plaintext.data(), plaintext.size());
    total_encrypted_length += encrypted_length;

    EVP_EncryptFinal_ex(ctx, (unsigned char*)encrypted_data.data() + total_encrypted_length, &encrypted_length);
    total_encrypted_length += encrypted_length;

    EVP_CIPHER_CTX_free(ctx);
    encrypted_data.resize(total_encrypted_length);

    return encrypted_data;
}

string generateRandomKey() {
    unsigned char key[16];

    if (RAND_bytes(key, sizeof(key)) != 1) {
        cerr << "Error generating random key\n";
        exit(1);
    }

    return string(reinterpret_cast<const char *>(key), sizeof(key));
}

string generateRandomByte(const int& size){
    unsigned char byte[size];

    if (RAND_bytes(byte, sizeof(byte)) != 1) {
        cerr << "Error generating random key\n";
        exit(1);
    }

    return string(reinterpret_cast<const char *>(byte), sizeof(byte));
}

pair<string, bool> encryptionOracle(const string& input) {
    string key = generateRandomKey();
    int prefixSize = rand() % 6 + 5;
    int suffixSize = rand() % 6 + 5;

    string text = generateRandomByte(prefixSize) + input + generateRandomByte(suffixSize);
    string ciphertext;

    pair<string, bool> out;
    // Se decide cual cifrado se usa
    if (rand()%2 == 0){
        // Usa ECB
        ciphertext = aes_ecb_encrypt(text, key);
        out.second = true;
    } else {
        // Usa CBC con iv aleatorio
        string iv = generateRandomKey();
        ciphertext = aes_cbc_encrypt(text, key, iv);
        out.second = false;
    }
    out.first = ciphertext;

    return out;
}

bool detectBlockCipherMode(const string& ciphertext) {
    // Divide el texto cifrado en bloques de 16 bytes
    int numBlocks = ciphertext.length() / 16;
    const int BLOCK_SIZE = 16;
    // Verifica si hay bloques idénticos en el texto cifrado
    for (int i = 0; i < ciphertext.length(); i += BLOCK_SIZE) {
        for (int j = i + BLOCK_SIZE; j < ciphertext.length(); j += BLOCK_SIZE) {
            if (ciphertext.substr(i, BLOCK_SIZE) == ciphertext.substr(j, BLOCK_SIZE)) {
                return true;
            }
        }
    }

    return false;  // No se encontraron bloques idénticos, probablemente se usa el modo CBC
}

pair<string, bool> fileTestB2E3(const string& filename){
    ifstream file(filename);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + filename;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string line, data;

    while (getline(file, line))
        data.append(line);

    return encryptionOracle(data);
}

string ecbencryptmyystringfile(const string& filename, const string& mystring, const string& key){
    ifstream file(filename);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + filename;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string line, data;

    while (getline(file, line))
        data.append(line);

    string base64Decode = base64_decode(data);
    string out = aes_ecb_encrypt(mystring + base64Decode, key);
    return out;
}

map<string, string> parsingRoutine(const string& input) {
    map<string, string> keyValueMap;
    size_t pos = 0;
    while (pos < input.length()) {
        size_t equalsPos = input.find('=', pos);
        size_t ampersandPos = input.find('&', pos);
        // string::npos hace referencia a cuando no se encuentra un valor
        if (equalsPos != string::npos && ampersandPos != string::npos && equalsPos < ampersandPos) {
            string key = input.substr(pos, equalsPos - pos);
            string value = input.substr(equalsPos + 1, ampersandPos - equalsPos - 1);
            keyValueMap[key] = value;
            pos = ampersandPos + 1;
        } else if (equalsPos != string::npos && (ampersandPos == string::npos || equalsPos < ampersandPos)) {
            string key = input.substr(pos, equalsPos - pos);
            string value = input.substr(equalsPos + 1);
            keyValueMap[key] = value;
            break;
        } else
            break;
    }

    return keyValueMap;
}

string profileFor(const string& email) {
    string sanitizedEmail;

    for (char c : email) {
        if (c == '&' || c == '=')
            continue; // Skip metacaracteres
        sanitizedEmail += c;
    }

    return "email=" + sanitizedEmail + "&uid=10&role=user";
}

string createAdminProfile(const string& email) {
    string encoded = profileFor(email);
    string key = generateRandomKey();
    string ciphertext = aes_ecb_encrypt(encoded, key);
    string cut_block = aes_ecb_encrypt("admin", key);
    string newciphertext = ciphertext.substr(0,ciphertext.size()-16) + cut_block;
    string sol = aes_ecb_decrypt(newciphertext, key);

    return sol;
}

int getBlockSize(const string& filename, const string& key) {
    string plaintext = "A";
    int initialLength = ecbencryptmyystringfile(filename, plaintext, key).length();

    int blockSize = 0;
    while (blockSize == 0) {
        plaintext += "A";
        int newLength = ecbencryptmyystringfile(filename, plaintext, key).length();
        if (newLength > initialLength)
            blockSize = newLength-initialLength;
    }

    return blockSize;
}

/*string attack_bit(int blockSize) {
    string dictionary;
    string inputBlock(blockSize - 1, 'A'); // Bloque de entrada con un byte menos

    // Generar diccionario de todos los posibles últimos bytes
    for (int c = 0; c <= 255; ++c) {
        dictionary = inputBlock + static_cast<char>(c);
        cout << dictionary << endl;
    }

    return dictionary;
}*/
