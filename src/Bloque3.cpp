#include "Bloque3.hpp"

string aes_ctr_encrypt(const string& key, vector<unsigned char> nonce, const string& input){
    AES_KEY aes_key;
    vector<unsigned char> output(input.length());
    vector<unsigned char> input_vector(input.begin(), input.end());
    vector<unsigned char> keystream(AES_BLOCK_SIZE);

    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aes_key);
    for (size_t i = 0; i < input.length(); i += AES_BLOCK_SIZE){
        AES_encrypt(nonce.data(), keystream.data(), &aes_key);
        size_t block_size = i + AES_BLOCK_SIZE <= input.length() ? AES_BLOCK_SIZE : (input.length() - i);
        for (size_t j = 0; j < block_size; j++)
            // Mira hacer esto con my xor
            output[i + j] = input_vector[i + j] ^ keystream[j];
        // Incrementar el contador
        ++nonce[8];
    }
    string sol(output.begin(), output.end());

    return sol;
}