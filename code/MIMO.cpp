#include <vector>
#include <complex>
#include <random>
#include <cmath>

std::vector<std::complex<double>> mimo_chanel(const std::vector<std::complex<double>>& symbols, 
const std::vector<std::vector<std::complex<double>>>& chanel_matrix, double snr_db = 0){

    const int size = symbols.size();

    std::vector<std::complex<double>> modulation_mimo(size);

    std::random_device rd ;
    std::mt19937 gen(rd ()) ;
    std::normal_distribution<double> dist(0.0, 1.0 / std::sqrt(2));


    std::complex<double> x0, x1;
    std::complex<double> noise0;
    std::complex<double> noise1;

    const double snr_times = std::pow(10, snr_db / 10.0);

    for(int i = 0; i < size / 2; ++i){

        noise0 = 1 / std::sqrt(snr_times) * std::complex<double>(dist(gen), dist(gen));

        noise1 = 1 / std::sqrt(snr_times) * std::complex<double>(dist(gen), dist(gen));

        x0 = symbols[2 * i];
       
        x1 = symbols[2 * i + 1];

        modulation_mimo[2 * i]  = x0 * chanel_matrix[0][0] + x1 * chanel_matrix[0][1] + noise0;

        modulation_mimo[2 * i + 1] = x0  * chanel_matrix[1][0] + x1 * chanel_matrix[1][1] + noise1;

    }

    return modulation_mimo;

}



std::vector<std::complex<double>> zf_equalizer(const std::vector<std::complex<double>>& mimo_symbols, 
const std::vector<std::vector<std::complex<double>>>& chanel_matrix){

    const int size = mimo_symbols.size();

    std::vector<std::complex<double>> demodulation_mimo(size);

    std::complex<double> det = chanel_matrix[0][0] * chanel_matrix[1][1] - chanel_matrix[0][1] * chanel_matrix[1][0];

    std::complex<double> y0, y1;

    std::vector<std::vector<std::complex<double>>> chanel_matrix_inv(2, std::vector<std::complex<double>>(2));

    chanel_matrix_inv[0][0] = chanel_matrix[1][1] / det;
    chanel_matrix_inv[0][1] = -chanel_matrix[0][1] / det;
    chanel_matrix_inv[1][0] = -chanel_matrix[1][0] / det;
    chanel_matrix_inv[1][1] = chanel_matrix[0][0] / det;


     for(int i = 0; i < size / 2; ++i){

        y0 = mimo_symbols[2 * i];
       
        y1 = mimo_symbols[2 * i + 1];

        demodulation_mimo[2 * i] = y0 * chanel_matrix_inv[0][0] + y1 * chanel_matrix_inv[0][1];
        demodulation_mimo[2 * i + 1] = y0  * chanel_matrix_inv[1][0] + y1 * chanel_matrix_inv[1][1];

    }


    return demodulation_mimo;
}