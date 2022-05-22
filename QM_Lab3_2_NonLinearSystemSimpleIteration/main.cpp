#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

/*System:
tg(xy+0.1) = x^2
x^2+2y^2=1 =>
==>
x = sqrt(tan(x*y+0.1))
y = sqrt((1-x*x)/2) => x0 = 1.25 doesn't work
*/

bool checkConvergence(double x, double y){
    string matrixA[2][2];
    matrixA[0][0] = "y/(2*cos(y*x+1/10)^2*sqrt(tan(y*x+1/10)))";
    matrixA[1][0] = "(-1)*x/(sqrt(2)*sqrt(1-x^2))";
    matrixA[0][1] = "x/(2*cos(x*y+1/10)^2*sqrt(tan(x*y+1/10)))";
    matrixA[1][1] = "                                  0";
    cout << "Matrix A:" << endl;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            cout << matrixA[i][j] << "   ";
        }
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------------" << endl;

    double matrixAZero[2][2];
    matrixAZero[0][0] = y/(2*cos((y*x+1.0/10)*(y*x+1.0/10))*sqrt(tan(y*x+1.0/10)));
    matrixAZero[1][0] = -x/(sqrt(2)*sqrt(1-x*x));
    matrixAZero[0][1] = x/(2*cos((x*y+1.0/10)*(x*y+1.0/10))*sqrt(tan(x*y+1.0/10)));
    matrixAZero[1][1] = 0;
    cout << "Matrix A0:" << endl;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            if (matrixAZero[i][j] == -0) cout << 0;
            else cout << matrixAZero[i][j];
            cout << "   ";
        }
        cout << endl;
    }
    cout << "---------------------------------------------------------------------------------------" << endl;

    double lNorm = max(abs(matrixAZero[0][0])+abs(matrixAZero[1][0]), abs(matrixAZero[0][1])+abs(matrixAZero[1][1]));
    cout << "L-norm of matrix A = " << lNorm;
    if (lNorm < 1){
        cout << " < 1" << endl;
        return true;
    }
    else cout << " > 1" << endl;
    return false;
}

void simpleIterator(double& x, double& y, const double EPSILON){
   double xPrev, yPrev;
   int iter = 0;

   do{
   xPrev = x;
   yPrev = y;
   x = sqrt(tan(xPrev*yPrev+0.1));
   y = sqrt((1-xPrev*xPrev)/2);

   cout << "Step " << ++iter << endl;
   cout << "x = " << x << endl;
   cout << "y = " << y << endl;

   }while(abs(max(x-xPrev, y-yPrev))>=EPSILON);

   cout << "---------------------------------------------------------------------------------------" << endl;
}

int main(){
    cout << setprecision(3);
    cout << fixed;

    const double EPSILON = 0.001;
    double x = 0;
    double y = 0;

    if(checkConvergence(x, y)){
        cout  << "There is convergence. Starting simple iteration method..." << endl;
        cout << "---------------------------------------------------------------------------------------" << endl;
    }
    else {
        cout << "There is no convergence. Sorry." << endl;
        return 0;
    }

    simpleIterator(x, y, EPSILON);

    cout << "Result: " << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
}
