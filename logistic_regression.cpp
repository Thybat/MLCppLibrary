#include <math.h>
#include <vector>
#include<iostream>
#include "logistic_regression.h"

std::vector<double> LogisticRegression::prediction(std::vector<double> theta, std::vector<std::vector<double> > dataset, double ceil)
{
    double sum_pred=0.0;
    std::vector<double> prediction;
    std::vector<double> probability;
    unsigned int i_col_label = dataset.size()-1;
    for (unsigned int i_features=0;i_features < dataset[0].size();i_features++)
     {
         sum_pred = theta[0];

     for (unsigned int i_col=0;i_col < dataset.size()-1; i_col++)//Iterate through number of prediction
        {
            sum_pred += theta[i_col+1]*dataset[i_col][i_features];
        }
        prediction.push_back(sum_pred);
     }
    for (auto &a : prediction)
        probability.push_back(1/(1-exp(a)));
    for (unsigned int i=0;i<probability.size();i++)
	if (probability[i] > ceil)
		std::cout << "probability " << i << " is superior to the ceil" << std::endl;
	else
		std::cout << "probability " << i << " is inferior to the ceil" << std::endl;
	return probability;
}
