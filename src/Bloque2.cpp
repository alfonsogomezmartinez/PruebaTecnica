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