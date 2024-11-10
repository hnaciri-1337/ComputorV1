#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Parser {
private:
    map<int, double> coefficients;

    vector<string> split(const string& s, char delimiter) {
        vector<string> tokens;
        string token;
        size_t start = 0;
        size_t end = s.find(delimiter, start);
        
        while (end != string::npos) {
            token = s.substr(start, end - start);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            start = end + 1;
            end = s.find(delimiter, start);
        }
        
        token = s.substr(start);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        
        return tokens;
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == string::npos)
            return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    void parseTerm(string term, bool isRightSide = false) {
        term = trim(term);
        if (term.empty())
            return;

        double sign = 1.0;
        if (term[0] == '-') {
            sign = -1.0;
            term = trim(term.substr(1));
        }
        if (isRightSide)
            sign = -sign;

        vector<string> parts = split(term, '*');
        if (parts.empty())
            return;

        double coef = stod(trim(parts[0])) * sign;

        int power = 0;
        if (parts.size() > 1) {
            string xPart = trim(parts[1]);
            if (xPart == "X")
                power = 1;
            else if (xPart.substr(0, 2) == "X^")
                power = stoi(xPart.substr(2));
        }

        coefficients[power] += coef;
    }

public:
    Parser() {}

    map<int, double> parse(const string& equation) {
        size_t equalPos = equation.find('=');
        if (equalPos == string::npos)
            throw invalid_argument("Invalid equation format");

        string leftSide = trim(equation.substr(0, equalPos));
        string rightSide = trim(equation.substr(equalPos + 1));

        if (leftSide[0] == '-')
            leftSide = "0" + leftSide;
        if (rightSide[0] == '-')
            rightSide = "0" + rightSide;

        vector<string> leftTerms = split(leftSide, '+');
        for (size_t i = 0; i < leftTerms.size(); i++) {
            vector<string> subTerms = split(leftTerms[i], '-');
            for (size_t j = 0; j < subTerms.size(); j++)
                if (!subTerms[j].empty()) {
                    if (j == 0)
                        parseTerm(subTerms[j]);
                    else
                        parseTerm("-" + subTerms[j]);
                }
        }

        vector<string> rightTerms = split(rightSide, '+');
        for (size_t i = 0; i < rightTerms.size(); i++) {
            vector<string> subTerms = split(rightTerms[i], '-');
            for (size_t j = 0; j < subTerms.size(); j++)
                if (!subTerms[j].empty()) {
                    if (j == 0)
                        parseTerm(subTerms[j], true);
                    else
                        parseTerm("-" + subTerms[j], true);
                }
        }

        return coefficients;
    }
};
