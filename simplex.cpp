#include "DifferentialEvolution.h"


#include <ctime>

using namespace std;

// the constraints for the parameters
const vector<pair<double, double>> CONSTRAINTS = {
        {-100.0, 100.0},
        {-100.0, 100.0},
        {-100.0, 100.0}
};

// the function we want to optimize
double my_pid(double p, double i, double d) {
    // run all the pid stuff and calculate the error (cost) (just the avg value between the setpoint and the actual value)
    // return the error
    return abs(42 - p + i + d);
}

class SimpleQuadriatic : public de::IOptimizable {
public:
    double EvaluteCost(std::vector<double> inputs) const override {
        assert(inputs.size() == 3);
//        cout << "x: " << inputs[0] << " y: " << inputs[1] << endl;

        double p = inputs[0];
        double i = inputs[1];
        double d = inputs[2];

        return my_pid(p, i, d);
    }

    unsigned int NumberOfParameters() const override {
        return 3;
    }

    std::vector<Constraints> GetConstraints() const override {
        std::vector<Constraints> constr(NumberOfParameters());
        for (unsigned int i = 0; i < NumberOfParameters(); ++i) {
            cout << "i: " << i << endl;
            cout << CONSTRAINTS[i].first << " " << CONSTRAINTS[i].second << endl;
            constr[i] = Constraints(CONSTRAINTS[i]);
        }
        return constr;
    }

    static bool terminalCondition(de::DifferentialEvolution de) {
        return de.GetBestCost() < 0.0001;
    }
};

int main() {
    SimpleQuadriatic cost;

    de::DifferentialEvolution de(cost, 100, 123, true, nullptr, SimpleQuadriatic::terminalCondition);

    de.Optimize(1000, true);

    return 0;
}