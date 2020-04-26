#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include "data_processing.h"
#include "linear_regression.h"

std::vector<double> LinearRegression::simple_linear_regression(std::vector<std::vector<double> > dataset)
{
    std::vector<double> mean_data;
    std::vector<double> coeff_b;
    mean_data = mean(dataset);
    double somme_num = 0, somme_den=0;
    for (unsigned int i=0;i<dataset[0].size();i++)
    {
        somme_num += (dataset[0][i]-mean_data[0])*(dataset[1][i]-mean_data[1]);
        somme_den += pow((dataset[0][i]-mean_data[0]),2);
    }
    std::cout << somme_num << std::endl;
    std::cout << somme_den << std::endl;
    double div_num_den = somme_num/somme_den;
    coeff_b.push_back(mean_data[1] - div_num_den*mean_data[0]);
    coeff_b.push_back(div_num_den);
    return coeff_b;
}

double LinearRegression::determ_coeff(std::vector<double> y_predict_values,std::vector<std::vector<double> > x_to_be_predicted,std::vector<std::vector<double> > dataset) //Fonction Incomplete PAS UTILISER
{
    std::vector<double> mean_data;
    mean_data = mean(dataset);
    double sst_ssr,sst=0.0;
    for (unsigned int i=0;i<y_predict_values.size();i++)
    {
        sst_ssr += pow(y_predict_values[i] - mean_data.back(),2);// mean[0] -> x mean[1] -> y
        sst += pow(x_to_be_predicted[x_to_be_predicted.size()-1][i] - mean_data.back(),2);
    }
    return sst/sst_ssr;
}

std::vector<double> LinearRegression::prediction(std::vector<double> theta, std::vector<std::vector<double> > dataset) // ok y'a deux fois la même fonction mais c'est pour réflechir plus vite
{
    double sum_pred=0.0;
    std::vector<double> prediction;
    unsigned int i_col_label = dataset.size()-1;
    for (unsigned int i_features=0;i_features < dataset[0].size();i_features++)
     {
         sum_pred = theta[0];

     for (unsigned int i_col=0;i_col < dataset.size()-1; i_col++)//Iterate through number of prediction
        {
            sum_pred += theta[i_col+1]*dataset[i_col][i_features];
        }
        std::cout << sum_pred << std::endl;
        prediction.push_back(sum_pred);
     }

    return prediction;
}
std::vector<double> LinearRegression::grad_cost_function(std::vector<double> theta, std::vector<std::vector<double> > dataset)
{
    std::vector<double> total_processed_pred;
    std::vector<double> cost_func;
    total_processed_pred = prediction(theta,dataset);//1 pour toutes les features et 1 par valeurs du tableau
    //Resize et a 0
    double each_elem_cost_func=0.0;
    unsigned int i_features = 0;
    unsigned int i_col = 0;
    unsigned int i_col_label = dataset.size()-1;
    for (i_col=0;i_col<dataset[0].size();i_col++)
        {
            //std::cout << total_processed_pred[nmbr_values] << nmbr_values;
            each_elem_cost_func += (total_processed_pred[i_col] - dataset[i_col_label][i_col]);
            //std::cout << each_elem_cost_func << ' ' << nmbr_values << '\n';
        }
    cost_func.push_back(each_elem_cost_func/dataset.size()); // Theta0

    for(i_features=0;i_features<i_col_label;i_features++)
    {
        each_elem_cost_func = 0.0;
        for ( i_col=0;i_col<dataset[0].size();i_col++)
        {
            //std::cout << total_processed_pred[nmbr_values] << nmbr_values;
            each_elem_cost_func += (total_processed_pred[i_col] - dataset[i_col_label][i_col]) * dataset[i_features][i_col];
        }
        cost_func.push_back(each_elem_cost_func/dataset.size());
    }
    //for (unsigned int i=0; i<cost_func.size();i++)
       //std::cout<< cost_func[i] << ' ' << i <<'\n';

   return cost_func;
}
std::vector<double> LinearRegression::grad_descent_iter(std::vector<std::vector<double> > dataset, double learning_rate)//grad_descent_iter
{
    std::vector <double> theta;
    std::vector <double> cost_func;
    unsigned int nb_features = dataset.size() -1;
    for(unsigned int j=0; j<dataset.size();j++)
        theta.push_back(static_cast <double> (rand())/(static_cast <double>(RAND_MAX/100.0))); //-10 et 10
    //pred = sum_pred(theta,dataset); //On calcule la somme de la prediction A ACTUALISER AVEC LES NVX THETA
    for (unsigned int i=0; i<100;i++)
    {

    cost_func = grad_cost_function(theta,dataset); // Creation des theta et calcul de la fonction de cout dérivee en fonction de chaque theta

    for (unsigned int nb_values=0;nb_values<dataset.size();nb_values++)
    {
        theta[nb_values] = theta[nb_values] - learning_rate * cost_func[nb_values];
        std::cout << theta[nb_values] << ' ' << nb_values << std::endl;
    }
    }

    return theta;
}
