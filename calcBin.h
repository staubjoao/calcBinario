#define BITS 16

#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void divisao(int Q[BITS], int M[BITS], int A[BITS]);
void zerarVetor(int *v);
int randomInt(int min, int max) { return min + rand() % (max + 1 - min); }
int deslocaDireita(int num[BITS], int c, int len);
int verificaZero(int num[BITS]);
int somaMult(int num1[BITS], int num2[BITS], int result[BITS], int len);
void multiplicacao(int Q[BITS], int M[BITS], int A[BITS], int lenQ, int lenM);
int menuSub(int num1[BITS], int num2[BITS], int result[BITS]);
int menuSoma(int num1[BITS], int num2[BITS], int result[BITS]);
void imprimeBin(int num[BITS]);
int potencia(int n, int x);
int binarioDec(int num[BITS]);
int verificaMaior(int num1[BITS], int num2[BITS]);
int verificaMaiorSemSinal(int num1[BITS], int num2[BITS]);
int somaBit(int b1, int b2, int b3, int *cout);
int soma(int num1[BITS], int num2[BITS], int result[BITS]);
int converteBinario(int num, int vet[BITS]);
int subtraiBit(int b1, int b2, int *cout);
void subtracao(int num1[BITS], int num2[BITS], int result[BITS]);