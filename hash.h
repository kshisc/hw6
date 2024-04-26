#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>

// #include <iostream> //delete

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
      // Add your code here
			unsigned long long w[5]={0}; //array of 0s
			std::string rev = k; //copy
			std::reverse(rev.begin(),rev.end());

			//split into groups of 6 and convert
			size_t length = rev.length();
			size_t groups = (length+5)/6;
			for(size_t i=0; i<groups; i++){
				size_t start = i*6;
				std::string sub = rev.substr(start,6);
				int index = 4-i;
				w[index]=convertToInteger(sub);
				// std::cout << index << " " << w[index] << std::endl;
			}

			//hash
			size_t hash = 0;
			for(int i=0; i<5; i++){
				hash+=rValues[i]*w[i];
			}
			return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T charToValue(char c) const
    {
        // Add code here or delete this helper function if you do not want it
				if(isdigit(c)){
					return c-'0'+26;
				}
				else if(isalpha(c)){
					return tolower(c)-'a';
				}
				else{
					return -1;
				}
  }

	//another helper function to convert 6 letter string to 64 bit integer
	unsigned long long convertToInteger(std::string& str) const{
		unsigned long long result=0;
		int power=0;
		for(size_t i=0; i<str.length(); i++){
			int value=charToValue(str[i]);
			result += value * static_cast<unsigned long long>(pow(36,power));
			power++;
		}
		return result;
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
