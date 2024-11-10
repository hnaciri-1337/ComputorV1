#include "Parser.hpp"
#include "Solver.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc != 2)
            throw invalid_argument("Invalid number of arguments");
        
        Parser parser;
        Solver solver(parser.parse(argv[1]));

        solver.printReducedForm();
        solver.printPolynomialDegree();
        solver.printSolution();
    }
    catch(const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
