#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

int generate_random_bit ();

std::vector<int> generate_bit_vector (int size);

double calculate_ber (const std::vector <int> &original, const std::vector <int> &received);

std::vector<std::complex<double>> bpsk_modulate (const std ::vector <int> &bits );

std::vector<int> bpsk_demodulate (const std::vector<std::complex<double>> &received );

std::complex<double> generate_channel_coef();

std::vector<std::vector<std::complex<double>>> generate_channel_matrix();

std::vector<std::complex<double>> mimo_channel(const std::vector<std::complex<double>>& symbols, 
const std::vector<std::vector<std::complex<double>>>& channel_matrix, double snr_db = 0);

std::vector<std::complex<double>> zf_equalizer(const std::vector<std::complex<double>>& mimo_symbols, 
const std::vector<std::vector<std::complex<double>>>& channel_matrix);