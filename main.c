#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>


struct Kart {
    char rank_simge;
    char *deck_simge;
    int deck;
    int rank;
    struct Kart *next;
};

struct Oyuncu {
    struct Kart *maca;
    struct Kart *karo;
    struct Kart *kupa;
    struct Kart *sinek;
    int puan;
    int ihale;
};

typedef struct Kart Kart;
typedef struct Kart* KartPtr;
typedef struct Oyuncu Oyuncu;
typedef struct Oyuncu* OyuncuPtr;

void deck_print(KartPtr kart) {
    while (1) {
        if (kart == NULL) {
            break;
        }
        else {
            if (kart->rank_simge == '0') {
                printf("10 - ");
            }
            else {
                printf("%c - ", kart->rank_simge);
            }
            kart = kart->next;
        }
    }
}

void oyuncu_kart_aktarim(KartPtr *deste, OyuncuPtr ana_oyuncu) {
    int i;
    // Sorting the assigned cards for the main player to their according decks

    for (i = 0; i < 13; i++) {
        int deck = deste[i]->deck;

        if (deck == 0) {
            if (ana_oyuncu->maca == NULL) {
                ana_oyuncu->maca = deste[i];
            }
            else {
                KartPtr kart = ana_oyuncu->maca;
                while (1) {
                    if (kart->next == NULL) {
                        kart->next = deste[i];
                        break;
                    }
                    else {
                        kart = kart->next;
                    }
                }
            }
        }
        else if (deck == 1) {
            if (ana_oyuncu->karo == NULL) {
                ana_oyuncu->karo = deste[i];
            }
            else {
                KartPtr kart = ana_oyuncu->karo;
                while (1) {
                    if (kart->next == NULL) {
                        kart->next = deste[i];
                        break;
                    }
                    else {
                        kart = kart->next;
                    }
                }
            }
        }
        else if (deck == 2) {
            if (ana_oyuncu->kupa == NULL) {
                ana_oyuncu->kupa = deste[i];
            }
            else {
                KartPtr kart = ana_oyuncu->kupa;
                while (1) {
                    if (kart->next == NULL) {
                        kart->next = deste[i];
                        break;
                    }
                    else {
                        kart = kart->next;
                    }
                }
            }
        }
        else if (deck == 3) {
            if (ana_oyuncu->sinek == NULL) {
                ana_oyuncu->sinek = deste[i];
            }
            else {
                KartPtr kart = ana_oyuncu->sinek;
                while (1) {
                    if (kart->next == NULL) {
                        kart->next = deste[i];
                        break;
                    }
                    else {
                        kart = kart->next;
                    }
                }
            }
        }
    }
}

void deste_karma (KartPtr *deste){
    int i;

    for (i = 0; i < 16; i++) {
        KartPtr kart = malloc(sizeof(Kart));
        kart->deck = i / 4;
        kart->rank = 13 - (i % 4);
        kart->next = NULL;

        if (kart->deck == 0) {
            kart->deck_simge = "♠";
        }
        else if (kart->deck == 1) {
            kart->deck_simge = "♦";
        }
        else if (kart->deck == 2) {
            kart->deck_simge = "♥";
        }
        else if (kart->deck == 3) {
            kart->deck_simge = "♣";
        }

        if (kart->rank == 13) {
            kart->rank_simge = 'A';
        }
        else if (kart->rank == 12) {
            kart->rank_simge = 'K';
        }
        else if (kart->rank == 11) {
            kart->rank_simge = 'Q';
        }
        else if (kart->rank == 10) {
            kart->rank_simge = 'J';
        }

        deste[i] = kart;
    }

    for (i = 0; i <= 36; i++) {
        KartPtr kart = malloc(sizeof(Kart));
        kart->deck = i / 9;
        kart->rank = (i % 9) + 2;
        if (kart->rank == 10) {
            kart->rank_simge = (char)(48);
        }
        else {
            kart->rank_simge = (char)(48 + ((i % 9) + 2));
        }
        kart->next = NULL;

        if (kart->deck == 0) {
            kart->deck_simge = "♠";
        }
        else if (kart->deck == 1) {
            kart->deck_simge = "♦";
        }
        else if (kart->deck == 2) {
            kart->deck_simge = "♥";
        }
        else if (kart->deck == 3) {
            kart->deck_simge = "♣";
        }

        deste[16 + i] = kart;
    }

    for (i = 0; i < 52; i++) {
        srand(time(NULL));
        int j = i + (rand()) % (52 - i);
        KartPtr temp = deste[i];
        deste[i] = deste[j];
        deste[j] = temp;
    }
}

void deck_siralama(KartPtr kart1) {
    if (kart1 != NULL) {
        while (kart1 != NULL) {
            KartPtr max = NULL;
            KartPtr kart2 = kart1->next;
            while (kart2 != NULL) {
                if (kart2->rank > kart1->rank) {
                    if (max == NULL) {
                        max = kart2;
                    }
                    else {
                        if (kart2->rank > max->rank) {
                            max = kart2;
                        }
                    }

                }
                kart2 = kart2->next;
            }

            if (max != NULL) {
                KartPtr temp_kart1_next = kart1->next;
                Kart temp_max = *max;
                KartPtr temp_max_next = max->next;

                *max = *kart1;
                max->next = temp_max_next;
                *kart1 = temp_max;
                kart1->next = temp_kart1_next;
            }
            kart1 = kart1->next;
        }
    }
}

int main(){
    KartPtr deste[52];

    deste_karma(deste);

    OyuncuPtr ana_oyuncu = malloc(sizeof(Oyuncu));
    ana_oyuncu->maca = NULL;
    ana_oyuncu->karo = NULL;
    ana_oyuncu->kupa = NULL;
    ana_oyuncu->sinek = NULL;

    oyuncu_kart_aktarim(deste, ana_oyuncu);

    // Sorting the cards inside the decks according to their values
    // Doesn't working atm
    deck_siralama(ana_oyuncu->maca);
    deck_siralama(ana_oyuncu->kupa);
    deck_siralama(ana_oyuncu->karo);
    deck_siralama(ana_oyuncu->sinek);




    
    printf("BATAK CONSOLE !\n\nBaşlamak için \"1\" girin\n");

    int start;
    scanf("%d", &start);

    if (start == 1) {
        printf("\e[1;1H\e[2J");
        printf("Oyuncu 1 : El sayısı belirleniyor...\n\n");
        printf("Oyuncu 2 : El sayısı belirleniyor...\n\n");
        printf("Oyuncu 3 : El sayısı belirleniyor...\n\n");
        printf("Siz : Alacağınız el sayısını girin\n\n");
        printf("Elinizdeki kartlar :\n\n");

        printf("♠ (Maça) : ");

        deck_print(ana_oyuncu->maca);

        printf("\n");
        printf("♦ (Karo) : ");

        deck_print(ana_oyuncu->karo);

        printf("\n");
        printf("♥ (Kupa) : ");

        deck_print(ana_oyuncu->kupa);

        printf("\n");
        printf("♣ (Sinek) : ");

        deck_print(ana_oyuncu->sinek);


        usleep(1000000000);
    }
    else {
        return 0;
    }


}