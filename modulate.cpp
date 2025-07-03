#include <vector>
#include <complex>
#include <iostream>

std::vector<std::complex<double>> bpsk_modulate ( const std::vector <int> &bits ){

    std::vector<std::complex<double>> result;

    result.reserve(bits.size());

    double modulation_bit;

    for(int bit : bits){
        modulation_bit = bit ? -1 : 1;
        result.push_back(std::complex<double>(modulation_bit, 0));
    }

    return result;
}


std::vector<int> bpsk_demodulate (const std::vector<std::complex<double>> &received ){

    std::vector<int> demodulate_bits;

    demodulate_bits.reserve(received.size());

    int demodulate_bit;
    
    for(std::complex<double> symbol : received){
        demodulate_bit = symbol.real() > 0 ? 0 : 1;
        demodulate_bits.push_back(demodulate_bit);
    }

    return demodulate_bits;
}
