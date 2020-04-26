#ifndef LINEAR_REGRESSION_H_INCLUDED
#define LINEAR_REGRESSION_H_INCLUDED
class LinearRegression
{
    public:
        std::vector<double> simple_linear_regression(std::vector<std::vector<double> >);
        double determ_coeff(std::vector<double> y_predict_values,std::vector<std::vector<double> > x_to_be_predicted,std::vector<std::vector<double> > dataset);
        std::vector<double> prediction(std::vector<double> theta, std::vector<std::vector<double> > dataset);
        std::vector<double> grad_cost_function(std::vector<double> theta, std::vector<std::vector<double> > dataset);
        std::vector<double> grad_descent_iter(std::vector<std::vector<double> > dataset, double learning_rate);
    private:
        std::vector<double> coeff;
};


#endif // LINEAR_REGRESSION_H_INCLUDED
