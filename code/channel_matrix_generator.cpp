#include <vector>
#include <complex>
#include <random>

std::complex<double> generate_channel_coef(){

    const double mean = 0.0;
    const double disp = 1 / std::sqrt(2);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<double> dist(mean, disp);

    return std::complex<double>(dist(gen), dist(gen));
}

std::vector<std::vector<std::complex<double>>> generate_channel_matrix(){

    std::vector<std::vector<std::complex<double>>> channel_matrix(2, std::vector<std::complex<double>>(2));

    for(std::vector<std::complex<double>>& row : channel_matrix){
        for(std::complex<double>& el : row){
            el = generate_channel_coef();
        }
    }

    return channel_matrix;

}