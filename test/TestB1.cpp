#include <gtest/gtest.h>
#include "../src/Bloque1.hpp"

TEST(Ejercicio1, Bloque1){
    string in = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    string out = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    EXPECT_EQ(out, StringHexToStringBase64(in));
}

TEST(Ejercicio2, Bloque1){
    string in1 = "1c0111001f010100061a024b53535009181c";
    string in2 = "686974207468652062756c6c277320657965";
    string out = "746865206b696420646f6e277420706c6179";
    EXPECT_EQ(out, XORBuffers(in1, in2));
}

TEST(Ejercicio3, Bloque1){
    string in = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    char out = 'X';
    EXPECT_EQ(out, FindKey(in));
}

TEST(Ejercicio4, Bloque1){
    string in = "../src/Bloque1Ejercicio4.txt";
    string out = "Now that the party is jumping\n";
    EXPECT_EQ(out, FindKeyFile(in));
}

TEST(Ejercicio5, Bloque1){
    string in = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string key = "ICE";
    string out = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    EXPECT_EQ(out, RepeatingKeyXOR(in, key));
}