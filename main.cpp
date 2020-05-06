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
    while (choice != 4)
    {
        std::cout << "Bonjour" << '\n' << "1. Test Linear Regression" << '\n' << "2. Test Prediction" << '\n' << "3. Knn" << '\n' <<"4. End Program" << '\n';
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
            for (unsigned int i = 0; i<test_regression.size();i++)
                std::cout << "Theta " << i << '\n' << test_regression[i] << '\n';
        }
        if (choice == 2)
        {
            split_dataset dataset_split;
            int nmbr_columns = 0;
            std::vector<double> zantoine;
            std::string csv = "data_reg_age_salary.csv";
            std::vector<std::string> initial_vector = csv_to_vector(csv, nmbr_columns);
            std::vector<std::vector<double> > data;
            std::vector<std::vector<double> > salary_predict;
            std::vector<double> predicted_y;
            salary_predict.resize(2);
            salary_predict[0].push_back(22);
            salary_predict[0].push_back(40);
            salary_predict[0].push_back(30);
            salary_predict[1].push_back(2000);
            salary_predict[1].push_back(3400);
            salary_predict[1].push_back(2750);
            data = vector_to_dataset(initial_vector,nmbr_columns);
            LinearRegression linear_regression;
            zantoine = linear_regression.simple_linear_regression(data);
            predicted_y = linear_regression.prediction(zantoine,salary_predict);
            for (unsigned int i = 0; i<zantoine.size();i++)
                std::cout << "Theta " << i << '\n' << zantoine[i]<< '\n';
            for (unsigned int y=0; y<salary_predict[0].size();y++)
            {
                std::cout << "salaire predit :" << predicted_y[y] << " a l'age de " << salary_predict[0][y] << " ans"  << '\n' ;
            }
        }
        if (choice == 3)
        {
            int nmbr_columns = 0;
            std::string csv2 = "iris2.csv";
            std::vector<std::string> initial_vector2 = csv_to_vector(csv2, nmbr_columns );
            std::vector< std::vector <double>> data2 = vector_to_dataset(initial_vector2,3);

            //calcul du vecteur distance, prend en entrée le dataset, la longeur et la largeur de notre fleur a estimer
            float choix_A, choix_B;
            std::cout<<"choix du critere A ( entre 0 et 7 ) "<<std::endl;
            std::cin>>choix_A;
            std::cout<<"choix du critere B ( entre 0 et 2.5 ) "<<std::endl;
            std::cin>>choix_B;

            std::vector<double> distances = calcl_vecteur_distance(data2,choix_A,choix_B);

            int choix_k, choix_k2;
            std::cout<<"choix k ?"<<std::endl;
            std::cin>>choix_k;
            std::vector<int> ind_min=trouver_min(distances,choix_k);
            afficher_classe(data2,  ind_min,  choix_k );



            std::vector<std::vector<double>> train = split_train(data2);
            std::vector<std::vector<double>> test = split_test(data2);

            std::cout<<"maintenant nous allons entrainer le model sur la moitie du dataset puis tester ces resutltat avec l autre moitie"<<std::endl;
            std::cout<<"pour tester la fiabilite du model"<<std::endl<<std::endl;
            std::cout<<"choix k 2 ?"<<std::endl;
            std::cin>>choix_k2;
            int classe_predite, classe_vraie, compteur=0;
            double nb_erreur=0;
            std::vector<double> distances2;
            std::vector<int> ind_min2;
            for (int cpt=0; cpt<train[0].size(); cpt++)
            {
                distances2 = calcl_vecteur_distance(train,test[0][cpt],test[1][cpt]);
                ind_min2=trouver_min(distances2,choix_k2);
                classe_predite=retourner_classe(train,  ind_min2,  choix_k2 );
                classe_vraie=test[2][cpt];
                if (classe_predite != classe_vraie)
                {
                    nb_erreur++;
                }

                compteur++;
            }
            double pourcentage_erreur, pourcentage_bon;
            pourcentage_erreur=(nb_erreur/compteur)*100;
            pourcentage_bon=((compteur-nb_erreur)/compteur)*100;
            std::cout<<"pourcentage erreur : "<<pourcentage_erreur<<"%"<<std::endl;
            std::cout<<"pourcentage bon : "<<pourcentage_bon<<"%"<<std::endl<<std::endl;
        }
    }
}
