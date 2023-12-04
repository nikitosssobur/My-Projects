#include <iostream>
#include <cmath>
#include <vector>
#include <array>
using namespace std;


double func(double t, double w){
    /*Right part function. You can write your own custom function.*/
    double output_value = sin(t + w);
    return output_value;
}

double func2(double t, double w){
    /*Another right part function.*/
    double output_value = cos(t + 2 * w);
    return output_value;
}

/*
float euler_method(double a, double b, int N, double initial_cond){
    double h = (b - a) / N;
    double t = a;
    double w = initial_cond;
    std::vector<std::array<double, 2>> output_array;
    output_array.push_back({t, w});
    for (int i = 1; i < N + 1; ++i){
        w = w + h * func(t, w);
        t = a + i * h;
        output_array.push_back({t, w});
    }
    return *output_array;    
}
*/

void PrintArray(vector<array<double, 2>> vect){
    cout << "[";
    for (int i = 0; i < vect.size(); i++)
    {
        if(i < vect.size() - 1)
        {
            cout << "[" << vect[i][0] << ", " << vect[i][1] << "],";
            cout << " ";
        }
        else
        {
            cout << "[" << vect[i][0] << ", " << vect[i][1] << "]";
        }
    }
    cout << "]";
}


vector<array<double, 2>> euler_method(double a, double b, int N, double initial_cond, double (*func)(double t, double w)){
    vector<array<double, 2>> output_vector;   
    double h = (b - a) / N, t = a, w = initial_cond;
    output_vector.push_back({t, w});
    
    for (int i = 1; i < N + 1; ++i){
        w += h * func(t, w);
        t += h; 
        output_vector.push_back({t, w});
    }
    return output_vector;
}


vector<array<double, 2>> heun_method(double a, double b, int N, double initial_cond, double (*func)(double t, double w)){
    vector<array<double, 2>> output_vector;
    double h = (b - a) / N, t = a, predictor = 0, corrector = initial_cond, slope = 0;
    output_vector.push_back({t, corrector});
    for (int i = 1; i < N + 1; ++i){
        slope = func(t, corrector);
        predictor = corrector + h * slope;
        t += h;
        corrector += (slope + func(t, predictor)) * h / 2;
        output_vector.push_back({t, corrector});
    }
    return output_vector;
}


vector<array<double, 2>> midpoint_method(double a, double b, int N, double initial_cond, double (*func)(double t, double w)){
    vector<array<double, 2>> output_vector;
    double h = (b - a) / N, t = a, midpoint, midpoint_value, w = initial_cond;
    output_vector.push_back({t, w});
    for (int i = 1; i < N + 1; ++i){
        midpoint_value = w + func(t, w) * h / 2;
        midpoint = (output_vector[i - 1][0] + t) / 2;
        w += func(midpoint, midpoint_value) * h;
        t += h;
        output_vector.push_back({t, w});
    }
    return output_vector;
}



int main(){
    double a, b, initial_cond;
    int N;
    vector<array<double, 2>> pairs_vector;
    vector<array<double, 2>> pairs_vector2;
    vector<array<double, 2>> pairs_vector3;
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input initial condition: ";
    cin >> initial_cond;
    cout << "Input N (number of points): ";
    cin >> N;
    if (a == b || N <= 0){
        cout << "Error! Invalid parameter values";
        return 1;
    }
    else{
        pairs_vector = euler_method(a, b, N, initial_cond, func);
        pairs_vector2 = heun_method(a, b, N, initial_cond, func);
        pairs_vector3 = midpoint_method(a, b, N, initial_cond, func);
        
        cout << "Result of computation for Newton's method: " << "\n\n";
        PrintArray(pairs_vector);
        
        cout << "\n\n Result of computation for Heun's method: " << "\n\n";
        PrintArray(pairs_vector2);

        cout << "\n\n Result of computation for Midpoint method: " << "\n\n";
        PrintArray(pairs_vector3);
        cout << "\n";

        
        vector<array<double, 2>> sol1, sol2, sol3;
        sol1 = euler_method(a, b, N, initial_cond, func2);
        sol2 = heun_method(a, b, N, initial_cond, func2);
        sol3 = midpoint_method(a, b, N, initial_cond, func2);
        
        cout << "Result of computation for Newton's method (func2): " << "\n\n";
        PrintArray(sol1);
        
        cout << "\n\n Result of computation for Heun's method (func2): " << "\n\n";
        PrintArray(sol2);

        cout << "\n\n Result of computation for Midpoint method (func2): " << "\n\n";
        PrintArray(sol3);
        cout << "\n";

        system("pause");
        return 0;
    }
}


