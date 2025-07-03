#include "header.hpp"

int main(){
    std::vector<double> snr_db_list;
    snr_db_list.reserve(20);

    const int NUM_BITS = 128;
    const int N_EXP = 2000;
    double real_ber, theory_ber;

    for(double snr = 0; snr < 14; snr += 0.2)
        snr_db_list.push_back(snr);

    std::vector<std::vector<std::complex<double>>> chanel_matrix;
    std::vector<int> transmitted;
    std::vector<std::complex<double>> modulated_symbols;
    std::vector<std::complex<double>> mimo_symbols;
    std::vector<std::complex<double>> mimo_zf;
    std::vector<int> recieved;


    for(double snr_db : snr_db_list){
        real_ber = 0;
        for(int i = 0; i < N_EXP; i++){
            chanel_matrix = generate_chanel_matrix();
            transmitted = generate_bit_vector(NUM_BITS);
            modulated_symbols = bpsk_modulate(transmitted);
            mimo_symbols = mimo_chanel(modulated_symbols, chanel_matrix, snr_db);
            mimo_zf = zf_equalizer(mimo_symbols, chanel_matrix);
            recieved = bpsk_demodulate(mimo_zf);
            real_ber += calculate_ber(transmitted, recieved);
        }

        real_ber /= N_EXP;
        theory_ber  = fabs(1 / (4 * snr_db));

        std::cout << "SNR in db = " << snr_db << ": Real BER = " << real_ber << " Theory BER = " << theory_ber <<'\n';
    }
}