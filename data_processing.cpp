#include<iostream>
#include<string>
#include<sstream>
#include<numeric>
#include<vector>
#include<fstream>
#include<algorithm>
#include<math.h>
#include"data_processing.h"
std::vector<std::string> csv_to_vector(std::string filename, int &nmbr_columns)//Simply transform a csv to a vector of strings
{
    std::ifstream ip;
    int total_line=0,total_comma=0;
    ip.open(filename.c_str()); //Require a char type
    if(!ip.is_open())
    {
       std::cout << " Error File not found" <<'\n';
    }
    std::string line;
    std::vector<std::string> get_csv;

    while(getline(ip,line))
    {
        std::stringstream ss(line);
        total_line++;
        while(getline(ss,line,','))
        {
            get_csv.push_back(line);
            total_comma++;
        }
    }
    nmbr_columns = total_comma/total_line;
    return get_csv;
}

std::vector<std::vector<double> > vector_to_dataset(std::vector<std::string> initial_vector, int nmbr_colmns)//Take this vector to build up a "Dataset" where Features are columns and data are lines.
{
    std::vector<std::vector<double> > dataset;
    dataset.resize(nmbr_colmns);
    initial_vector.erase(initial_vector.begin(),initial_vector.begin()+nmbr_colmns);//Popping Strings to avoid error due to double type
    int counter = 0;
    for(int y=0; y<nmbr_colmns;y++)
    {
        for(unsigned int i = y; i<initial_vector.size();i=i+nmbr_colmns)//Using counter to process the two indices correctly avoiding if and modulos
                dataset[counter].push_back(stod(initial_vector[i]));
        counter++;
    }
    initial_vector.clear();
    return dataset;
}

std::vector<double> mean(std::vector<std::vector <double> > dataset)//Output a vector of the mean for each columns
{
    std::vector<double> mean_vect;
    double s_dataset = dataset[0].size();
    for (unsigned int i=0;i<dataset.size();i++)
        mean_vect.push_back( accumulate(dataset[i].begin(), dataset[i].end(), 0.0)/s_dataset);
    return mean_vect;
}
std::vector<double> sum(std::vector<std::vector<double> > dataset)//Output the sum of each columns
{
    std::vector<double> sum_vect;
    for (unsigned int i=0;i<dataset.size();i++)
        sum_vect.push_back(accumulate(dataset[i].begin(),dataset[i].end(),0.0));
    return sum_vect;
}
std::vector<std::vector<double> > min_max_scaler(std::vector<std::vector<double> > dataset, const int nmbr_columns)//Just a normal MinMaxScaler
{
    std::vector<std::vector<double> > min_maxed;
    min_maxed.resize(nmbr_columns);
    double min_max_array[nmbr_columns][2] = {};

    unsigned int i,j;
    for (i = 0;i<dataset.size();i++)
    {
        min_max_array[i][0] = dataset[i][0];//Initialise minimum value to avoid min = 0
        for(j = 0;j<dataset[i].size();j++)
            if (min_max_array[i][1]<dataset[i][j]) // min_max_array[i][1] = maximum; [0] = minimum
                min_max_array[i][1] = dataset[i][j];
            else if (min_max_array[i][0]> dataset[i][j])
                min_max_array[i][0] = dataset[i][j];
    }
    for (i = 0;i<dataset.size();i++)
        for(j = 0;j<dataset[i].size();j++)
            min_maxed[i].push_back((dataset[i][j] - min_max_array[i][0])/(min_max_array[i][1]-min_max_array[i][0]));
    return min_maxed;
}
std::vector<std::vector<double> > put_column_as_label(std::vector<std::vector<double> > dataset, unsigned int colmn_replaced)//Maths for the library is based on the fact that the label is the last columns
{
    dataset.push_back(std::vector<double>());
    for(unsigned int line = 0; line < dataset[0].size(); line++)
            dataset[dataset.size()-1].push_back(dataset[colmn_replaced][line]);
    dataset.erase(dataset.begin()+colmn_replaced);
    return dataset;
}

split_dataset data_test_train_split(std::vector<std::vector<double> > dataset, double ratio_dataset)//Split a dataset in a NON RANDOM way based on a coefficient
{

    split_dataset dataset_split;
    double ratio_train=0,ratio_test=0;
    unsigned int nmbr_colmns = dataset.size();
    unsigned int total_size = dataset[0].size();
    ratio_train = floor(total_size*ratio_dataset);
    ratio_test = total_size - ratio_train;
    dataset_split.data_test.resize(nmbr_colmns);
    dataset_split.data_train.resize(nmbr_colmns);
    for (unsigned int i=0; i<nmbr_colmns;i++)
        for (unsigned int j=0;j<ratio_test;j++)
               dataset_split.data_test[i].push_back(dataset[i][j]);
    for (unsigned int x=0; x<nmbr_colmns;x++)
        for (unsigned int y=ratio_test;y<total_size;y++)
            dataset_split.data_train[x].push_back(dataset[x][y]);
    return dataset_split;
}
void print_dataset(std::vector<std::vector<double> > dataset)//Print a 2D vector
{
    for(unsigned int col=0;col<dataset.size();col++)
        for(unsigned int line=0;line<dataset[0].size();line++)
            std::cout << dataset[col][line] <<'\n';
}
void print_vector(std::vector<double> vect)//Print a simple vector
{
    for(auto &a : vect)
        std::cout << a  << '\n';
}
