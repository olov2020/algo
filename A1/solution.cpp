#include <iostream>
#include <cmath>
#include <fstream>

unsigned long seed = 1;

unsigned long MyRand() {
    seed = seed * 1103515245 + 12345;
    return seed / 65536 % 32768;
}

bool GenerateCoords(int min, int max) {
    double x = min + static_cast<double>(MyRand()) / RAND_MAX * (max - min);
    double y = min + static_cast<double>(MyRand()) / RAND_MAX * (max - min);
    return x * x + y * y <= 1;
}

std::string MakeString(double pi, double PI, double a) {
    std::string ans = std::to_string(pi);
    ans += ";";
    ans += std::to_string(PI);
    ans += ";";
    ans += std::to_string(a);
    ans += ";";
    return ans;
}

int main() {
    std::ofstream fout("output.csv");
    for (int n = 100; n <= 5000; n += 100) {
        int m = 0;
        for (int i = 0; i < n; ++i) {
            m += GenerateCoords(-1, 1);
        }
        double pi = 4.0 * m / n;
        double PI = M_PI;
        double a = (PI - pi) / PI  * 100;
        std::cout << MakeString(pi, PI, a) << '\n';
        fout << MakeString(pi, PI, a) << '\n';
    }
    fout.close();
}
