#ifndef DATA_PROCESSING_H_INCLUDED
#define DATA_PROCESSING_H_INCLUDED
#include<iostream>
#include<string>
#include<sstream>
#include<numeric>

struct split_dataset{
std::vector<std::vector<double> > data_train;
std::vector<std::vector<double> > data_test;
};
split_dataset data_test_train_split(std::vector<std::vector<double> > dataset, double ratio_dataset);
std::vector<std::string> csv_to_vector(std::string filename, int& nmbr_columns);
std::vector<std::vector<double> > vector_to_dataset(std::vector<std::string> initial_vector, int nmbr_colmns);
std::vector<double> mean(std::vector<std::vector <double> > dataset);
std::vector<double> sum(std::vector<std::vector<double> > dataset);
std::vector<std::vector<double> > min_max_scaler(std::vector<std::vector<double> > dataset,int nmbr_columns);

#endif // DATA_PROCESSING_H_INCLUDED
