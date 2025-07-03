#include <iostream>
#include <random>
#include <vector>

int generate_random_bit () {
    std :: random_device rd ;
    std :: mt19937 gen (rd ()) ;
    std :: uniform_int_distribution < > dis (0, 1);
    return dis (gen);
}


std::vector<int> generate_bit_vector (int size) {
    std::vector<int> bit_vector;
    bit_vector.reserve(size);

    int rand_bit;
    
    for(int i = 0; i < size; ++i){
        rand_bit = generate_random_bit();
        bit_vector.push_back(rand_bit);
    }

    return bit_vector;
}
