#ifndef KNN_H_INCLUDED
#define KNN_H_INCLUDED
#include<iostream>
#include<string>
#include<sstream>
#include<numeric>

double calc_distance(double length_tab,double width_tab, double length_fix, double width_fix);
std::vector<double> calcl_vecteur_distance(std::vector<std::vector<double>> data, double length_est, double width_est);
std::vector<int> trouver_min(std::vector<double> distances,int choix_k );
void afficher_classe( std::vector<std::vector<double>> data, std::vector<int> ind_min, int choix_k );
std::vector<std::vector<double>> split_train ( std::vector<std::vector<double>> data );
std::vector<std::vector<double>> split_test ( std::vector<std::vector<double>> data );
int retourner_classe( std::vector<std::vector<double>> data, std::vector<int> ind_min, int choix_k );



#endif // KNN_H_INCLUDED
