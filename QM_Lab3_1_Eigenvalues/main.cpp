#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<vector<int>> MatrixInt;
typedef vector<double> Vector;

Vector operator*(const Matrix& matrix , const Vector& vec){
    Vector result (vec.size() , 0);
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

double findA(const Matrix& matrix){
     double result = -1;
     Vector temp (matrix.size(), 0);
     for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            temp[i] += abs(matrix[i][j]);
        }
     }
     for (int i = 0; i < matrix.size(); i++){
        result = max(result, temp[i]);
     }
     return result;
}

double normalize(const Vector& vec) {
        double norm = 0;
        for (double v : vec) {
            norm += v*v;
        }
        return sqrt(norm);
    }

double GetMaxEigenValue(const Matrix& matrix, const double epsilon){

    Vector Xn(matrix.size(), 1);
    Vector Xn1(matrix.size());

    double lambda = 0;
    double lambdaPrev = 0;
    int iter = 0;

    do {
        Xn1 = matrix * Xn;

        lambdaPrev = lambda;

        double nominator = 0;
        int ind = 0;
        for (int i = 0; Xn1.size(); i++){
            if (Xn1[i]){
                nominator = Xn1[i];
                ind = i;
                break;
            }
        }

        lambda = nominator / Xn[ind];

        double norm = normalize(Xn1);

        for (int i = 0; i < Xn1.size(); i++) {
            Xn1[i] /= norm;
        }

        Xn = Xn1;

        cout << "Step " << ++iter << endl;
        cout << "Max eigenvalue of B = " << lambda << endl;

        } while (abs(lambda - lambdaPrev) > epsilon);
        cout << "----------------------------" << endl;
        return lambda;
}
int main()
{
    cout << setprecision(3);
    cout << fixed;

    const double EPSILON = 0.001;

    Matrix matrix =
      {
    {2 , 1 , 0 },
    {1 , 2 , 1 },
    {0 , 1 , 2 }
    };


    double a = findA(matrix);
    cout << "M-norm of matrix A is " << a << endl;
    cout << "----------------------------" << endl;

     /*Finding A*E matrix*/
    MatrixInt E;
    for (int i = 0; i < matrix.size(); i++) {
        vector<int> v1;
        for (int j = 0; j < matrix.size(); j++) {
            v1.push_back(0);
        }
        E.push_back(v1);
    }
    for(int i = 0; i < matrix.size(); i++){
        E[i][i] += a;
    }

    cout << "Matrix B:" << endl;

    /*Finding B matrix*/
   for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            matrix[i][j] -= 2*matrix[i][j] - E[i][j];
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------" << endl;

    double answer = a -  GetMaxEigenValue(matrix , EPSILON);
    cout << "Min eigenvalue of the initial matrix = " << answer << endl;
}



