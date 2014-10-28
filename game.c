#define MAXSIZE 100

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

long long int table[MAXSIZE][MAXSIZE];
int p, p1, p2, p3, g;

void start();

int check_index(int, int, int, int), check_range(int, int, int, int);

int check_step(int, int, int, int);

void replace(int, int, int, int), output(), input();

int check_win(int), check_fail();

void game_with_time(), game_for_win(), game_for_score(), help();

void finish(int);

long long int score(long long int[MAXSIZE][MAXSIZE]);

main(int argc, char *argv[])
{
    srand(time(NULL));
    help();
    if (*++argv[1] == 'w')
        game_for_win();
    else if (*argv[1] == 's')
        game_for_score();
    else if (*argv[1] == 't')
        game_with_time();
    return 0;
}

void game_for_win() /* while not win */
{
    printf("What number you want to finish the game? ");
    long long int k;
    scanf("%d", &k);
    start();
    output();
    while (!check_win(k) && !check_fail()) {
        input();
        if (check_step(p, p1, p2, p3)) {
            replace(p, p1, p2, p3);
            output();
        }
        else {
            printf("\nError: wrong index of numbers\n");
        }
    }
    finish(check_fail());
}

void game_for_score() /* game without win or time rules. Only fail can finish it. */ 
{
    start();
    output();
    while (!check_fail()) {
        input();
        if (check_step(p, p1, p2, p3)) {
            replace(p, p1, p2, p3);
            output();
        }
        else
            printf("\nError: wrond index of numbers\n");
    }
    finish(check_fail());
}

void game_with_time() /* game with time rules */ 
{
    printf("How many time you want to play (min)? ");
    int k;
    scanf("%d", &k);
    start();
    output();
    int time_1 = time(NULL);
    int time_2 = 0;
    while (((time_2 - time_1) <= k * 60) && !check_fail()) {
        input();
        if (check_step(p, p1, p2, p3)) {
            replace(p, p1, p2, p3);
            output();
        }
        else
            printf("\nError: wrong index of numbers\n");
        time_2 = time(NULL);
    }
    finish(check_fail());
}

long long int score(long long int q[MAXSIZE][MAXSIZE]) /* function counts score on the desk */
{
    long long int k, h;
    h = 0;
    k = 0;
    int i, x;

    for (i = 0; i < g; i++) {
        for (x = 0; x < g; x++)
            k += q[i][x]; 
        h += k;
        k = 0;
        }
    return h;
}

int check_win(int u)
{
    if (score(table) >= u)
        return 1;
    return 0;
}

void finish(int l)
{
    if (l == 1)
        printf("You are looser... Your score is %lld\n", score(table));
    else
        printf("You are winner! Your score is %lld\n", score(table));
}

int check_step(int v, int v1, int v2, int v3) /* function checks user's steps */
{
    if (check_index(v, v1, v2, v3)) {
        if (table[v][v1] == table[v2][v3])
            return 1;
    }return 0;
}

void start()
{
    printf("Choose the size of game desk (not very big; depends on the size\nof your screen): ");
    scanf("%d", &g);

    int i, x;
    for (i = 0; i < g; i++) {
        for (x = 0; x < g; x++) {
            if (rand() <= ((double) (RAND_MAX / 2))) 
                table[i][x] = 2;
            else
                table[i][x] = 4;
        }
    }
}

void output()
{
    int i, x;
    for (i = g-1; i >= 0; i--) {
        for (x = 0; x <= g-1; x++)
            printf("%6lld", table[i][x]);
        printf("\n");
    }
}

void input()
{
    printf("Enter index1 with index2 for the first number and index3 with index4 for the second: ");
    scanf("%d %d %d %d", &p, &p1, &p2, &p3);
}

void replace(int a, int b, int c, int d) /* replace numbers desribed by a user */
{
    table[c][d] = table[a][b] * 2;
    while (a != g-1) {
        table[a][b] = table[a+1][b];
        a++;
    }if (rand() <= ((double) (RAND_MAX / 2)))
         table[g-1][b] = 4;
    else
        table[g-1][b] = 2;
}

int check_range(int a, int b, int c, int d)
{
    if ((a >= 0) && (b >= 0) && (c >= 0) && (d >= 0) && (a < g) && (b < g) &&(c < g) && (d < g))
        return 1;
    return 0;
}
int check_index(int a, int b, int c, int d)
{
    if (((((c == a + 1) || (c == a - 1)) && (d == b)) || (((d == b + 1) || (d == b - 1)) && (c == a))) && check_range(a, b, c, d))
        return 1; 
    return 0;
}

int check_fail()
{
    int i, x, z, c;
    
    for (i = 0; i < g; i++) {
        for (x = 0; x < g; x++) {
            for (z = 0; z < g; z++) {
                for (c = 0; c < g; c++) {
                    if (check_index(i, x, z, c) && table[z][c] == table[i][x]) 
                        return 0;
                }
            }
        }
    }return 1;
}

void help()
{
    printf("Use options: -w for playing while your score < number\nyou want; -t for playing with time and -s for playing while not fail.\nGame is very easy: choose the index of number1 and index of number2\nusing this format: \"number1 number2 number3 number4\" (where number1\nwith number2 are index of the first number and number3 with\nnumber4 - of the second). The first number must be = the second number\nand it must be near it. When you take this numbers, gravity will work.\n"); 
}
