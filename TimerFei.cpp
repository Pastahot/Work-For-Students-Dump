#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

int main()
{
    char ch;
    clock_t start_time, end_time;
    double elapsed_time;
    srand(time(NULL));  // inicializácia generátora náhodných čísel
    setlocale(LC_ALL, "C");  // set locale to use dot as decimal separator

    printf("Stlac F1 pre napovedu, F2 pre zacatie merania, F10 alebo ESC pre ukoncenie programu.\n");

    while (1) {
        ch = _getch();  // použitie funkcie _getch() namiesto getch()

        if (ch == 0) {  // kontrola, či ide o špeciálnu klávesu
            ch = _getch();  // načítanie ďalšej časti špeciálnej klávesy
            if (ch == 59) {  // F1
                printf("Napoveda:\n");
                printf("Stlac F2 pre zacatie merania.\n");
                printf("Stlac F10 alebo ESC pre ukoncenie programu.\n");
            }
            else if (ch == 60) {  // F2
                printf("Zacalo meranie.\n");
                printf("Stlac rovnaku klavesu pre ukoncenie merania.\n");

                while (1) {
                    char random_char = rand() % 26;
                    random_char = (random_char < 13) ? 'a' + random_char : 'A' + (random_char - 13); // generovanie náhodného písmena (A-Z, a-z)
                    printf("Stlacene pismeno: %c\n", random_char);  // výpis náhodného písmena

                    start_time = clock();  // začiatok merania
                    while (1) {
                        char input = _getch();  // načítanie stlačenej klávesy
                        if (toupper(input) == toupper(random_char)) {  // kontrola, či bola stlačená rovnaká klávesa ako náhodné písmeno
                            end_time = clock();  // koniec merania
                            elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;  // trvanie merania v sekundách a milisekundách
                            printf("Cas: %.3lf s\n", elapsed_time);  // výpis zmeraného času

                            printf("\n");

                            break;
                        }
                        else if (input == 27 || input == 68) {  // ESC alebo F10
                            exit(0);
                        }
                    }
                }
            }
            else if (ch == 68 || ch == 27) {  // F10 alebo ESC
                exit(0);

            }
        }
    }

    return 0;
}