#ifndef HASH_H
#define HASH_H

#include <ctype.h>
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long sums[5];
        unsigned long long hash = 0;
        for(int j = k.length() - 6; j >= -5; j -= 6){
            int nJ = j;
            if(j < 0){
                nJ = 0;
            }
            unsigned long long sum = 0;
            // Add your code here
            for(int i = nJ; i < k.length() && i < 6 + j; i++){
                sum *= 36;
                sum += letterDigitToNumber(k[i]);
            }
            sums[5 - (k.length() - j) / 6] = sum;
            //std::cout << sum << std::endl;
            //std::cout << rValues[5 - (k.length() - j) / 6] << std::endl;
            hash += sum * rValues[5 - (k.length() - j) / 6];
        }
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter >= 'A' && letter <= 'Z'){
            letter = tolower(letter);
        }
        if(letter >= '0' && letter <= '9'){
            return letter - '0' + 26;
        }
        else{
            return letter - 'a';
        }
        return NULL;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
