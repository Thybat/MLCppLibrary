#ifndef LOGISTIC_REGRESSION_H_INCLUDED
#define LOGISTIC_REGRESSION_H_INCLUDED

class LogisticRegression
{
    public:
        std::vector<double> prediction(std::vector<double> theta, std::vector<std::vector<double> > dataset, double ceil);
};


#endif // LOGISTIC_REGRESSION_H_INCLUDED
