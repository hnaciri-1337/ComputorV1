#include <map>
#include <iostream>
#include "Math.hpp"

using namespace std;

class Solver {
private:
    map<int, double>    coefficients;
    int                 degree;
public:
    Solver(map<int, double> coefficients) : coefficients(coefficients) {
        degree = 0;
        for (auto it = coefficients.begin(); it != coefficients.end(); it++)
            if (it->second != 0)
                degree = it->first;
    }

    void printReducedForm() {
        cout << "Reduced form: ";
        for (int currDegree = 0; currDegree <= degree; currDegree++) {
            if (currDegree == 0) {
                if (coefficients[currDegree] < 0)
                    cout << "- ";
            }
            else {
                if (coefficients[currDegree] < 0)
                    cout << " - ";
                else
                    cout << " + ";
            }
            cout << abs(coefficients[currDegree]) << " * X^" << currDegree;
        }
        cout << " = 0" << endl;
    }

    void printPolynomialDegree() {
        cout << "Polynomial degree: ";
        cout << degree << endl;
    }

    void printSolution() {
        if (degree == 0) {
            if (coefficients[0] == 0)
                cout << "All real numbers are solutions !" << endl;
            else
                cout << "No solution !" << endl;
        }
        else if (degree == 1) {
            cout << "The solution is:" << endl;
            cout << (coefficients[0] * -1) / coefficients[1] << endl;
        }
        else if (degree == 2) {
            double a = coefficients[2];
            double b = coefficients[1];
            double c = coefficients[0];
            double delta = ft::pow(b, 2) - (4 * a * c);

            if (delta == 0) {
                cout << "The solution is:" << endl;
                cout << (b * -1) / (2 * a) << endl;
            }
            else if (delta > 0) {
                cout << "Discriminant is strictly positive, the two solutions are:" << endl;
                cout << ((b * -1) - ft::sqrt(delta)) / (2 * a) << endl;
                cout << ((b * -1) + ft::sqrt(delta)) / (2 * a) << endl;
            }
            else {
                cout << "Discriminant is strictly negative, the two complex solutions are:" << endl;
                cout << (b * -1) / (2 * a) << " - i * " << ft::sqrt(-delta) / (2 * a) << endl;
                cout << (b * -1) / (2 * a) << " + i * " << ft::sqrt(-delta) / (2 * a) << endl;
            }
        }
        else {
            throw invalid_argument("The polynomial degree is stricly greater than 2, I can't solve.");
        }
    }
};
