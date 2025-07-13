#include <vector>
#include <iostream>

double calculate_ber ( const std::vector <int> &original, const std::vector <int> &received){

    if(original.size() != received.size())
        return -1;

    int errors = 0;

    double total_ber;

    for(int i = 0; i < original.size(); ++i){
        if(original[i] != received[i])
            errors++;
    }

    total_ber = errors / (double)(original.size());
    
    return total_ber;
}
