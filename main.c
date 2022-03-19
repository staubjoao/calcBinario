#include <stdio.h>
#include <stdlib.h>

#define BITS 16

int somaBit(int b1, int b2, int b3, int *cout);
void soma(int num1[BITS], int num2[BITS], int result[BITS]);
void converteBinario(int num, int vet[BITS]);
int subtraiBit(int b1, int b2, int b3, int *cout);
void subtracao(int num1[BITS], int num2[BITS], int result[BITS]);

int main()
{
  int vetNum1[BITS], vetNum2[BITS], result[BITS], num1, num2, i;
  char op;

  printf("Digite o primeiro número: ");
  scanf("%d", &num1);
  printf("Digite a operação (+, -, * e /): ");
  fflush(stdin);
  scanf("%c", &op);
  fflush(stdin);
  printf("Digite o segundo número: ");
  scanf("%d", &num2);

  converteBinario(num1, vetNum1);
  converteBinario(num2, vetNum2);

  for (i = 0; i < BITS; i++)
    printf("%d", vetNum1[i]);
  printf("\n");
  for (i = 0; i < BITS; i++)
    printf("%d", vetNum2[i]);
  printf("\n");

  if (op == '+')
  {
    if (vetNum2[0] == 1)
      subtracao(vetNum1, vetNum2, result);
    soma(vetNum1, vetNum2, result);
  }
  else if (op == '-')
  {
    if (vetNum2[0] == 1)
      soma(vetNum1, vetNum2, result);
    subtracao(vetNum1, vetNum2, result);
  }
  else if (op == '*')
  {
  }
  else if (op == '/')
  {
  }

  for (i = 0; i < BITS; i++)
    printf("%d", result[i]);
  printf("\n");
  return 0;
}

int somaBit(int b1, int b2, int b3, int *cout)
{
  *cout = (b1 + b2 + b3) / 2;
  return ((b1 + b2 + b3) % 2);
}

void soma(int num1[BITS], int num2[BITS], int result[BITS])
{
  int i, aux = 0;
  for (i = 15; i > 0; i--)
    result[i] = somaBit(num1[i], num2[i], aux, &aux);
  result[i] = aux;
}

int subtraiBit(int b1, int b2, int b3, int *cout)
{
  int c = b1 - b2;
  if (c < 0)
    c = 1, *cout = 1;
  return c;
}

void subtracao(int num1[BITS], int num2[BITS], int result[BITS])
{
  int i, aux = 0;
  for (i = 15; i > 0; i--)
  {
    result[i] = subtraiBit(num1[i], num2[i], aux, &aux);
    if (num1[i] - num2[i] < 0)
      num1[i - 1] = num1[i - 1] - aux;
  }
  result[i] = 0;
}

void converteBinario(int num, int vet[BITS])
{
  int i, aux = num;
  if (num < 0)
    num = num * -1;

  for (i = BITS - 1; i >= 0; i--)
  {
    if (num % 2 == 0)
      vet[i] = 0;
    else
      vet[i] = 1;
    num /= 2;
  }
  if (aux < 0)
    vet[0] = 1;
}