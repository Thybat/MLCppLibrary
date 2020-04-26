#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <math.h>
#include <iomanip>
#include "data_processing.h"
#include "linear_regression.h"

// Structure de donnée : une feature est dans une colonne exemple : toutes les features de 0 a n pour la variable y -> [n][0], une ligne -> une nouvelle variable

int main()
{

    split_dataset dataset_split;
    int nmbr_columns = 0;
    double r_2 = 0.0;
    std::vector<double> mean_data;
    std::vector<double> zantoine;
    std::string csv = "data_reg_age_salary.csv";
    std::vector<std::string> initial_vector = csv_to_vector(csv, nmbr_columns);
    std::vector<std::vector<double> > data;
    std::vector<std::vector<double> > normalized_data;
    data = vector_to_dataset(initial_vector,nmbr_columns);
    normalized_data = min_max_scaler(data,nmbr_columns);
    LinearRegression linear_regression;
    std::vector<double> test_regression;
    for (unsigned int i=0;i<normalized_data.size();i++)
        for (unsigned int j=0;j<normalized_data[0].size();j++)
            std::cout << normalized_data[i][j] << std::endl;
    //test_regression = linear_regression.grad_descent_iter(normalized_data,0.01);
    //std::cout << test_regression[0] << ' ' << test_regression[1]<< std::endl;
}
