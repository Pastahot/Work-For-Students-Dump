def f(x):
    # Parabolická funkcia pre prierez polomeru
    return 0.003 * x ** 2

def volume(r, h):
    # Výpočet objemu valca s polomerom r a výškou h
    return 3.14159265358979323846 * r ** 2 * h

def sqrt(x):
    # Výpočet odmocniny čísla x pomocou babylonskej metódy
    guess = x / 2.0
    result = x

    while guess != result:
        result = guess
        guess = (x / guess + guess) / 2.0

    return result

def pow(x, y):
    # Výpočet x umocnené na y pomocou cyklu
    result = 1.0

    for i in range(int(y)):
        result *= x

    return result

# Rozmery suroviny
r_s = 85.0 / 2.0
h_s = 150.0

# Počet vzoriek
n = 100

# Interval vzoriek
delta_x = 70.0 / n

x = 0.0
volume_waste = 0.0

for i in range(n):
    r = 2 * f(x)
    length = sqrt(delta_x ** 2 + pow(f(x + delta_x) - f(x), 2))
    v = volume(r, length)

    volume_waste += v
    x += delta_x

# Výpočet objemu odpadu
v_shaft = volume(r_s, h_s) - volume_waste

print("Odhadovaný objem odpadového materiálu je", volume_waste, "kubických milimetrov.")
print("Odhadovaný objem hriadeľa je", v_shaft, "kubických milimetrov.")
