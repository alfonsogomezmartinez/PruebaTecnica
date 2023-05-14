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
    EXPECT_EQ(out, findKey(in));
}
