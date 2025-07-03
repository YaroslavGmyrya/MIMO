#include "header.hpp"

int main(){
    const std::vector<double> snr_db_list{-1.0, -0.5, 
                                          0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0
                                        };
    const int NUM_BITS = 512;
    const int N_EXP = 1000;
    double ber;

    std::vector<std::vector<std::complex<double>>> chanel_matrix;
    std::vector<int> transmitted;
    std::vector<std::complex<double>> modulated_symbols;
    std::vector<std::complex<double>> mimo_symbols;
    std::vector<std::complex<double>> mimo_zf;
    std::vector<int> recieved;


    for(double snr_db : snr_db_list){
        ber = 0;
        for(int i = 0; i < N_EXP; i++){
            chanel_matrix = generate_chanel_matrix();
            transmitted = generate_bit_vector(NUM_BITS);
            modulated_symbols = bpsk_modulate(transmitted);
            mimo_symbols = mimo_chanel(modulated_symbols, chanel_matrix, snr_db);
            mimo_zf = zf_equalizer(mimo_symbols, chanel_matrix);
            recieved = bpsk_demodulate(mimo_zf);
            ber += calculate_ber(transmitted, recieved);
        }

        ber /= N_EXP;

        std::cout << "SNR in db = " << snr_db << ": BER = " << ber << '\n';
    }
}