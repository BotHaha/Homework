#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double t_s = 0.08;
    double t_l = 0.02;
    double t_t = 0.001;
    int S = 2000;
    int n = 200000;
    int m = 64;

    cout << "k\tt_input (sec)" << endl;
    for (int k = 2; k <= 64; k *= 2) {
        int rounds = ceil(log(m) / log(k));
        double blocks = static_cast<double>(n) / S;
        double t_block = t_s + t_l + S * t_t;
        double t_input = rounds * blocks * t_block;
        cout << k << "\t" << t_input << endl;
    }
    return 0;
}
