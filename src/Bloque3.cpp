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
            output[i + j] = input_vector[i + j] ^ keystream[j];
        // Incrementar el contador
        ++nonce[8];
    }
    string sol(output.begin(), output.end());

    return sol;
}

vector<vector<unsigned char>> transpose(const vector<std::vector<unsigned char>>& matrix) {
    // Obtener las dimensiones de la matriz original
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Crear una nueva matriz transpuesta con las dimensiones invertidas
    vector<vector<unsigned char>> transposed(cols, vector<unsigned char>(rows));

    // Copiar los elementos de la matriz original a la transpuesta
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            transposed[j][i] = matrix[i][j];

    return transposed;
}

string attack_ctr(const string& filename){
    ifstream file(filename);

    try{
        if (!file.is_open()){
            string typeError = "No se pudo abrir el archivo: " + filename;
            throw typeError;
        }
    } catch (const string& typeError) {
        cout << "Error: " << typeError << endl;
    }

    string line, line_decode, cipherline;
    string key = GLOBALKEY;
    AES_KEY aes_key;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aes_key);
    vector<vector<unsigned char>> concatened;

    while (getline(file, line)){
        vector<unsigned char> nonce(16, 0);
        vector<unsigned char> keystream(AES_BLOCK_SIZE);
        string output;

        line_decode = base64_decode(line);
        cipherline = aes_ctr_encrypt(GLOBALKEY, nonce, line_decode);
        vector<unsigned char> cipherline_vector(cipherline.begin(), cipherline.end());
        concatened.push_back(cipherline_vector);
    }

    vector<vector<unsigned char>> concatened_trans = transpose(concatened);
    vector<vector<unsigned char>> plaintext;
    for(size_t i = 0;i < concatened_trans.size(); ++i) {
        int maxScore = 0;
        string aux;

        for (int j = 0; j < 256; ++j) {

            string xoredBytes = XORCharacter(concatened_trans[i], j);

            // Calcular la puntuación para el resultado actual
            int score = ScoreEnglish(xoredBytes);

            // Actualiza la clave y la puntuación máxima si es necesario
            if (score > maxScore) {
                maxScore = score;
                aux = xoredBytes;
            }
        }

        vector<unsigned char> aux_vector(aux.begin(), aux.end());
        plaintext.push_back(aux_vector);
    }
    vector<vector<unsigned char>> sol = transpose(plaintext);
    string sol_text;
    for (size_t i = 0; i < sol.size(); ++i) {
        string sol_aux(sol[i].begin(), sol[i].end());
        sol_text.append(sol_aux);
    }

    return sol_text;
}