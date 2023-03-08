#include <iostream>
#include <cmath>

double f(double x) {
    // Parabolická funkcia pre prierez polomeru
    return 0.003 * x * x;
}

double volume(double r, double h) {
    // Výpočet objemu valca s polomerom r a výškou h
    return M_PI * r * r * h;
}

int main() {
    // Rozmery suroviny
    double r_s = 85.0 / 2.0;
    double h_s = 150.0;

    // Počet vzoriek
    int n = 100;

    // Interval vzoriek
    double delta_x = 70.0 / n;

    double x = 0.0;
    double volume_waste = 0.0;

    for (int i = 0; i < n; i++) {
        double r = 2 * f(x);
        double length = sqrt(delta_x * delta_x + pow(f(x + delta_x) - f(x), 2));
        double v = volume(r, length);

        volume_waste += v;
        x += delta_x;
    }

    // Výpočet objemu odpadu
    double v_shaft = volume(r_s, h_s) - volume_waste;

    std::cout << "Odhadovaný objem odpadového materiálu je " << volume_waste << " kubických milimetrov." << std::endl;
    std::cout << "Odhadovaný objem hriadeľa je " << v_shaft << " kubických milimetrov." << std::endl;

    return 0;
}
