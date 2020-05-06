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
#include "knn.h"

// Structure de donnée : une feature est dans une colonne exemple : toutes les features de 0 a n pour la variable y -> [n][0], une ligne -> une nouvelle variable

int main()
{
    int choice =0;
    while (choice != 3)
    {
        std::cout << "Bonjour" << '\n' << "1. Test Linear Regression" << '\n' << "2. Knn" << '\n' << "3. End Program" << '\n';
        std::cin >> choice;
        if (choice == 1)
        {
            split_dataset dataset_split;
            int nmbr_columns = 0;
            std::string csv = "data_reg_age_salary.csv";
            std::vector<std::string> initial_vector = csv_to_vector(csv, nmbr_columns);
            std::vector<std::vector<double> > data;
            std::vector<std::vector<double> > normalized_data;
            std::vector<std::vector<double> > last_label_colm;
            data = vector_to_dataset(initial_vector,nmbr_columns);
            normalized_data = min_max_scaler(data,nmbr_columns);
            LinearRegression linear_regression;
            //last_label_colm = put_column_as_label(normalized_data,0);
            std::vector<double> test_regression;
            test_regression = linear_regression.grad_descent_iter(normalized_data, 0.1);
                std::cout << test_regression[0] << ' ' << test_regression[1]<< std::endl;
        }
        if (choice == 2)
        {
            std::string csv2 = "iris2.csv";
            int nmbr_columns = 0;
            std::vector<std::string> initial_vector2 = csv_to_vector(csv2 , nmbr_columns );
            std::vector< std::vector <double>> data2 = vector_to_dataset(initial_vector2,3);

            //calcul du vecteur distance, prend en entrée le dataset, la longeur et la largeur de notre fleur a estimer
            std::vector<double> distances = calcl_vecteur_distance(data2,2.8,0.6);

            int choix_k; //choix du nombre de voisin a prendre en compte
            std::cout<<"choix k ?"<<std::endl;
            std::cin>>choix_k;
            //trouve les k indices dans le dataset pour lesquels la distance est minimale ( choisir k impair )
            std::vector<int> ind_min=trouver_min(distances,choix_k);
            //affiche a quelle classe ca correspond
            afficher_classe(data2,  ind_min,  choix_k );
        }

    }


}
