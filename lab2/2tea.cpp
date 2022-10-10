#include <fstream>
#include <iostream>

#define DELTA 0x9e3779b9
#define NUMBER_OF_ROUNDS 32
using namespace std;

void encrypt(uint32_t* text, const uint32_t* key){
    unsigned int y = text[0], z = text[1], sum = 0, n = NUMBER_OF_ROUNDS;
    while(n-- > 0){
        sum += DELTA;
        y += ((z << 4) + key[0]) ^ (z + sum) ^ ((z >> 5) + key[1]);
        z += ((y << 4) + key[2]) ^ (y + sum) ^ ((y >> 5) + key[3]);
    }
    text[0] = y;
    text[1] = z;
}

void decrypt(uint32_t* text, const uint32_t* key){
    unsigned int y = text[0], z = text[1], sum = DELTA << 5, n = NUMBER_OF_ROUNDS;
    while(n-- > 0){
        z -= ((y << 4) + key[2]) ^ (y + sum) ^ ((y >> 5) + key[3]);
        y -= ((z << 4) + key[0]) ^ (z + sum) ^ ((z >> 5) + key[1]);
        sum -= DELTA;

    }
    text[0] = y;
    text[1] = z;
}

string split(const uint32_t* values){
    string splitOut;
    splitOut += (unsigned char)(values[0] & 0xFF);
    splitOut += (unsigned char)(values[0] >> 8);
    splitOut += (unsigned char)(values[0] >> 16);
    splitOut += (unsigned char)(values[0] >> 24);

    splitOut += (unsigned char)(values[1] & 0xFF);
    splitOut += (unsigned char)(values[1] >> 8);
    splitOut += (unsigned char)(values[1] >> 16);
    splitOut += (unsigned char)(values[1] >> 24);

    return splitOut;
}

void combine(const unsigned char* str, uint32_t* values){
    values[0] = str[0] | str[1] << 8 | str[2] << 16 | str[3] << 24;
    values[1] = str[4] | str[5] << 8 | str[6] << 16 | str[7] << 24;
}



int main() {
    string inputString;
    uint32_t key[4] = {1, 1, 1, 1};
    ifstream f1(R"(C:\Users\hp\Documents\in.txt)");\
    f1 >> inputString;
    unsigned int len = inputString.length();
    unsigned int newLen = 0;
    if (len % 8 != 0)
        newLen = len + (8 - len % 8);

    for (uint32_t i = 0; i < newLen - len; ++i){
        char c = 0x0;
        inputString += c;
    }
    cout << "Input String" << endl;
    cout << inputString << endl << endl;

    unsigned int rounds = newLen/8;

    string outString;
    uint32_t values[2];
    unsigned char turn[9]= "";

    for(uint32_t i = 0 ; i < rounds ; i++) {
        for (int j = 0; j < 8; j++) {
            turn[j] = inputString[i * 8 + j];
        }
        combine(turn, values);
        encrypt(values, key);
        outString +=split(values);
    }

    cout << "Encrypted String with key: " << key << endl;
    cout << outString << endl << endl;

    string decryptString;
    for(uint32_t i = 0 ; i < rounds ; i++) {
        for (int j = 0; j < 8; j++) {
            turn[j] = outString[i * 8 + j];
        }
        combine(turn, values);
        decrypt(values, key);
        decryptString += split(values);

    }

    cout << "Decrypted String with key: " << key << endl;
    cout << decryptString << endl;
    f1.close();

    return 0;
}
