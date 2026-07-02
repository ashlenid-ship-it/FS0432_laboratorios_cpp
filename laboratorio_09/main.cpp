#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

double f(double x, double t)
{
    return -x + sin(t);
}

double exacta(double t)
{
    return 0.5 * (sin(t) - cos(t))
           + 1.5 * exp(-t);
}

void euler(
    vector<double>& t,
    vector<double>& x_num,
    vector<double>& x_exa,
    vector<double>& error,
    double t0,
    double tf,
    double h,
    double x0
)
{
    int N = static_cast<int>((tf - t0) / h);

    t.push_back(t0);

    x_num.push_back(x0);

    x_exa.push_back(exacta(t0));

    error.push_back(
        fabs(x0 - exacta(t0))
    );

    for(int n = 0; n < N; n++)
    {
        double t_next = t[n] + h;

        double x_next =
            x_num[n]
            + h * f(x_num[n], t[n]);

        double x_exact =
            exacta(t_next);

        double err =
            fabs(x_next - x_exact);

        t.push_back(t_next);

        x_num.push_back(x_next);

        x_exa.push_back(x_exact);

        error.push_back(err);
    }
}

int main()
{
    double t0 = 0.0;

    double tf = 10.0;

    double h = 0.1;

    double x0 = 1.0;

    vector<double> t;

    vector<double> x_num;

    vector<double> x_exa;

    vector<double> error;

    euler(
        t,
        x_num,
        x_exa,
        error,
        t0,
        tf,
        h,
        x0
    );

    cout << fixed << setprecision(6);

    cout << "t\tEuler\t\tExacta\t\tError\n";

    double error_max = 0.0;

    for(size_t i = 0; i < t.size(); i++)
    {
        cout << t[i] << "\t"
             << x_num[i] << "\t"
             << x_exa[i] << "\t"
             << error[i] << endl;

        if(error[i] > error_max)
        {
            error_max = error[i];
        }
    }

    cout << "\nError maximo = "
         << error_max << endl;

    plt::figure();

    plt::named_plot(
        "Euler",
        t,
        x_num
    );

    plt::named_plot(
        "Exacta",
        t,
        x_exa
    );

    plt::title("Metodo de Euler");

    plt::xlabel("t");

    plt::ylabel("x(t)");

    plt::legend();

    plt::save("solucion_euler.png");

    plt::figure();

    plt::named_plot(
        "Error",
        t,
        error
    );

    plt::title("Error absoluto");

    plt::xlabel("t");

    plt::ylabel("Error");

    plt::legend();

    plt::save("error_local.png");

    plt::show();

    return 0;
}