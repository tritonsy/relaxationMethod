#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
    int n;
    double eps,omega;
    ifstream f("matrix.txt");
    f >> n;
    f >> eps;
    f >> omega;
    double **a = new double *[n+1]; //Выделяем память под строки
    for (int i = 1; i <= n; i++)
        a[i] = new double[n+1];     //Под столбцы
    double b[n + 1];
    double x[n + 1];
    cout << "Matrix A: " << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f >> a[i][j];
            cout << a[i][j] << ' ';
        }
        f >> b[i];
        cout << b[i] <<endl;
        x[i] = b[i]/ a[i][i];
    }
    f.close();

    double NextX[n + 1];
    int k = 0;
    double norm;
    do {
        norm=0;
        for (int i = 1; i <= n; ++i) {
            double sum = 0;
            for (int j = 2; j <= n; ++j) {
                if (i != j) {
                    sum = sum + a[i][j] * x[j];
                }
            }
            double Next = (1-omega)*x[i] + omega*(b[i] - sum) / a[i][i];

            if (fabs(Next - x[i]) > norm) {
                norm = fabs(Next - x[i]);
            }
            x[i] = Next;
        }
        k++;
    } while (norm > eps);

    cout << "Iteration count: " << k << endl << "eps: " << eps << endl;
    norm=0;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j) {
            b[i] = b[i] - a[i][j] * x[j];
        }
        if (norm < fabs(b[i])) {
            norm = fabs(b[i]);
        }
    }
    cout << "Residual= " << norm << endl;

    //Выводим решения
    ofstream out ("answer.txt");
    cout <<endl <<"Answer" <<endl;
    for (int i = 1; i <= n; i++) {
        cout << setprecision(10) << fixed << x[i] << " ";
        out << x[i] << ' ';
    }
    out.close();
    return 0;
}