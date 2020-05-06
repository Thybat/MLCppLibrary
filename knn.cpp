#include<iostream>
#include<string>
#include<sstream>
#include<numeric>
#include<vector>
#include<fstream>
#include<algorithm>
#include<math.h>
#include"Knn.h"

//permet de calculer la distance euclydienne
double calc_distance(double length_tab,double width_tab,double length_fix,double width_fix)
{
    return sqrt((length_fix-length_tab)*(length_fix-length_tab)+ (width_fix-width_tab)*(width_fix-width_tab));
}

//permpet de calculer les distances avec les données de data et de renvoyer un vecteur qui contient les distances
std::vector<double> calcl_vecteur_distance(std::vector<std::vector<double>> data, double length_est, double width_est)
{
    std::vector<double> distances;
    for (int i=0; i<data[0].size(); i++)
    {
        distances.push_back(calc_distance(data[0][i],data[1][i],length_est,width_est));
    }
    return distances;
}
//permet de renvoyer un vecteur contenant l'indice des distances minimales
std::vector<int> trouver_min(std::vector<double> distances,int choix_k )
{
    int k=0;//compteur
    float indice_min;//variables qui va prendre la distance min
    float distance_min=distances[0];//on initialise distance min
    std::vector<int> ind_min;//vector contenant l'indice des distances minimales

    while(k < choix_k)
    {
        for ( int i=1; i<distances.size(); i++ )
        {

            if( distances[i] <= distance_min && distances[i]>=0)
            {
                distance_min=distances[i];
                indice_min=i;

            }

        }
        ind_min.push_back(indice_min);//on ajoute l'indice de la plus petite valeur dans le tableau
        distances[indice_min]=-1;//on remplace par -1 pour ne plus prendre cette valeur lors du prochain passage dans la boucle

        k=k+1;
        //on renitialise les valeurs
        distance_min=distances[0];
        indice_min=0;
    }
    return ind_min;
}

void afficher_classe( std::vector<std::vector<double>> data, std::vector<int> ind_min, int choix_k )
{
    int classe1=0;
    int classe2=0;
    int classe3=0;

    for(int i=0; i<choix_k; i++)
    {
        if(data[2][ind_min[i]]==0)
        {
            classe1=classe1+1;
        }

        if(data[2][ind_min[i]]==1)
        {
            classe2=classe2+1;
        }

        if(data[2][ind_min[i]]==2)
        {
            classe3=classe3+1;
        }
    }
    if ( classe1>classe2 && classe1 >classe3)
    {
        std::cout<<"c est la classe 0 "<<std::endl<<std::endl;
    }
    if ( classe2>classe1 && classe2 >classe3)
    {
        std::cout<<"c est la classe 1 "<<std::endl<<std::endl;
    }
    if ( classe3>classe1 && classe3 >classe2)
    {
        std::cout<<"c est la classe 2 "<<std::endl<<std::endl;
    }
    std::cout<<"voisin de classe 0 : "<<classe1<<std::endl;
    std::cout<<"voisin de classe 1 : "<<classe2<<std::endl;
    std::cout<<"voisin de classe 2 : "<<classe3<<std::endl<<std::endl;
}

int retourner_classe( std::vector<std::vector<double>> data, std::vector<int> ind_min, int choix_k )
{
    int classe1=0, classe2=0, classe3=0;


    for(int i=0; i<choix_k; i++)
    {
        if(data[2][ind_min[i]]==0)
        {
            classe1=classe1+1;
        }

        if(data[2][ind_min[i]]==1)
        {
            classe2=classe2+1;
        }

        if(data[2][ind_min[i]]==2)
        {
            classe3=classe3+1;
        }
    }
    if ( classe1>classe2 && classe1 >classe3)
    {
        return 0;
    }
    if ( classe2>classe1 && classe2 >classe3)
    {
        return 1;

    }
    if ( classe3>classe1 && classe3 >classe2)
    {
        return 2;

    }
}


std::vector<std::vector<double>> split_train ( std::vector<std::vector<double>> data )
{
    std::vector<std::vector<double>> train;
    train.resize(data.size());
    for ( int i = 0; i<data.size(); i++)
    {
        for (int j=0; j<data[0].size()-1; j=j+2)
        {

            train[i].push_back(data[i][j]);
        }
    }
    return train;
}

std::vector<std::vector<double>> split_test ( std::vector<std::vector<double>> data )
{
    std::vector<std::vector<double>> test;
    test.resize(data.size());
    for ( int i = 0; i<data.size(); i++)
    {
        for (int j=1; j<data[0].size(); j=j+2)
        {

            test[i].push_back(data[i][j]);
        }
    }
    return test;
}
