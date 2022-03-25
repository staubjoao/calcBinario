#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calcBin.h"

int main()
{
  int vetNum1[BITS], vetNum2[BITS], result[BITS], num1, num2, i, resultDec;
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
    result[i] = 0;

  if (op == '+')
  {
    menuSoma(vetNum1, vetNum2, result);
    resultDec = binarioDec(result);
    printf("(%d) + (%d) = %d  |  %s", num1, num2, num1 + num2, resultDec == num1 + num2 ? "certo" : "errado");
  }
  else if (op == '-')
  {
    menuSub(vetNum1, vetNum2, result);
    resultDec = binarioDec(result);
    printf("(%d) - (%d) = %d  |  %s", num1, num2, num1 - num2, resultDec == num1 - num2 ? "certo" : "errado");
  }
  else if (op == '*')
  {
  }
  else if (op == '/')
  {
  }

  return 0;
}

void menuSub(int num1[BITS], int num2[BITS], int result[BITS])
{
  int x = verificaMaior(num1, num2);
  if (num1[0] == 0 && num2[0] == 0) // x - y
  {
    if (x == 2)
      subtracao(num2, num1, result), result[0] = 1;
    else
      subtracao(num1, num2, result);
  }
  else if (num1[0] == 0 && num2[0] == 1) // x - (-y)
    soma(num1, num2, result);
  else if (num1[0] == 1 && num2[0] == 0) // -x - y
    soma(num1, num2, result), result[0] = 1;
  else if (num1[0] == 1 && num2[0] == 1) //-x -(-y)
  {
    if (x == 2)
      subtracao(num2, num1, result);
    else
      subtracao(num1, num2, result), result[0] = 1;
  }
}

void menuSoma(int num1[BITS], int num2[BITS], int result[BITS])
{
  if (num1[0] == 0 && num2[0] == 0) // x + y
    soma(num1, num2, result);
  else if (num1[0] == 0 && num2[0] == 1) // x + (-y)
    num2[0] = 0, menuSub(num1, num2, result);
  else if (num1[0] == 1 && num2[0] == 0) // -x + y
    num1[0] = 0, menuSub(num1, num2, result);
  else if (num1[0] == 1 && num2[0] == 1) // -x + (-y)
    soma(num1, num2, result), result[0] = 1;
}

void imprimeBin(int num[BITS])
{
  for (int i = 0; i < BITS; i++)
    printf("%d", num[i]);
  printf("\n");
}

int potencia(int n, int x)
{
  if (x == 0)
    return 1;
  else if (x == 1)
    return n;
  else
    return potencia(n, x - 1) * n;
}

int binarioDec(int num[BITS])
{
  int n = 0, aux = 0;
  for (int i = BITS - 1; i > 0; i--, aux++)
  {
    if (num[i] == 1)
      n += potencia(2, aux);
  }
  if (num[0] == 1)
    n = n * -1;
  return n;
}

int verificaMaior(int num1[BITS], int num2[BITS])
{
  if (num1[0] == 1 && num2[0] == 0)
    return 2;
  else if (num1[0] == 0 && num2[0] == 1)
    return 1;
  else
  {
    for (int i = 1; i < BITS; i++)
    {
      if (num1[i] > num2[i])
        return 1;
      else if (num2[i] > num1[i])
        return 2;
    }
    return 0;
  }
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

int subtraiBit(int b1, int b2, int *cout)
{
  int c = b1 - b2;
  if (c < 0)
    c = 1, *cout = 1;
  return c;
}

void subtracao(int num1[BITS], int num2[BITS], int result[BITS])
{
  int i, j, aux = 0;
  for (i = 15; i > 0; i--)
  {
    result[i] = subtraiBit(num1[i], num2[i], &aux);
    if (aux == 1)
    {
      j = i - 1;
      while (num1[j] != 1)
        num1[j] = 1, j--;
      num1[j] = 0, aux = 0;
    }
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