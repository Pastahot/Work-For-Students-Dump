#include <iostream>

double f(double x) {
    // Parabolická funkcia pre prierez polomeru
    return 0.003 * x * x;
}

double volume(double r, double h) {
    // Výpočet objemu valca s polomerom r a výškou h
    return 3.14159265358979323846 * r * r * h;
}

double sqrt(double x) {
    // Výpočet odmocniny čísla x pomocou babylonskej metódy
    double hadana = x / 2.0;
    double vysledok = x;

    while (hadana != vysledok) {
        vysledok = hadana;
        hadana = (x / hadana + hadana) / 2.0;
    }

    return vysledok;
}

double pow(double x, double y) {
    // Výpočet x umocnené na y pomocou cyklu
    double vysledok = 1.0;

    for (int i = 0; i < y; i++) {
        vysledok *= x;
    }

    return vysledok;
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
