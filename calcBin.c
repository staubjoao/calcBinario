#include "calcBin.h"

int main()
{
  int aux, vetNum1[BITS], vetNum2[BITS], result[BITS], restoMod, num1, num2, resultDec, lenNum1, lenNum2;
  char op;

  // srand(time(NULL));
  do
  {
    // printf("Digite o primeiro número: ");
    // scanf("%d", &num1);
    // printf("Digite a operação (+, -, * e /): ");
    // fflush(stdin);
    // scanf("%c", &op);
    // fflush(stdin);
    // printf("Digite o segundo número: ");
    // scanf("%d", &num2);
    num1 = 32767;
    num2 = 1;
    op = '-';
    zerarVetor(result);
    zerarVetor(vetNum1);
    zerarVetor(vetNum2);
    lenNum1 = converteBinario(num1, vetNum1);
    lenNum2 = converteBinario(num2, vetNum2);

    if (op == '+')
    {
      if (menuSoma(vetNum1, vetNum2, result) == -1)
        printf("Overflow!\n");
      else
      {
        resultDec = binarioDec(result);
        printf("(%4d) + (%4d) = %4d  |  %s  %4d\n", num1, num2, num1 + num2, resultDec == num1 + num2 ? "certo" : "errado", resultDec);
      }
    }
    else if (op == '-')
    {
      if (menuSub(vetNum1, vetNum2, result) == -1)
        printf("Overflow!\n");
      else
      {
        resultDec = binarioDec(result);
        printf("(%4d) - (%4d) = %4d  |  %s  %4d\n", num1, num2, num1 - num2, resultDec == num1 - num2 ? "certo" : "errado", resultDec);
      }
    }
    else if (op == '*')
    {
      if (verificaZero(vetNum1) == 1 || verificaZero(vetNum2) == 1)
        printf("(%4d) * (%4d) = %4d  |  %s\n", num1, num2, num1 * num2, "certo");
      else
      {
        multiplicacao(vetNum1, vetNum2, result, lenNum1, lenNum2);
        resultDec = binarioDec(result);
        printf("(%4d) * (%4d) = %4d  |  %s  %4d\n", num1, num2, num1 * num2, resultDec == num1 * num2 ? "certo" : "errado", resultDec);
      }
    }
    else if (op == '/')
    {
      if (verificaZero(vetNum2))
        printf("Não existe divisão por 0\n");
      else
      {
        if (verificaMaiorSemSinal(vetNum1, vetNum2) == 2)
        {
          printf("O segundo número é maior que o primeiro, incapaz de gerar número decimal\n");
        }
        else
        {
          divisao(vetNum1, vetNum2, result);
          resultDec = binarioDec(result);
          restoMod = binarioDec(vetNum1);
          printf("(%4d) / (%4d) = %4d  resto: %4d  |  %s  %4d\n", num1, num2, num1 / num2, num1 % num2, resultDec == num1 / num2 && restoMod == num1 % num2 ? "certo" : "errado", resultDec);
        }
      }
    }

    zerarVetor(vetNum1);
    zerarVetor(vetNum2);
    zerarVetor(result);
    printf("Deseja realizar outra operação? 0 para não e 1 para sim: ");
    scanf("%d", &aux);
  } while (aux != 0);
  return 0;
}

void subZero(int num1[BITS], int num2[BITS])
{
  num1[0] = 1;
  for (int i = 1; i < BITS; i++)
    num1[i] = num2[i];
}

void divisao(int Q[BITS], int M[BITS], int A[BITS])
{
  int m, cont = 0, aux;
  do
  {
    subtracao(Q, M, Q);
    cont++;
    m = verificaMaiorSemSinal(Q, M);
  } while (m == 1 || m == 0);
  converteBinario(cont, A);
  if (Q[0] == 1 && M[0] == 1)
    Q[0] = 1, A[0] = 0;
  else if (Q[0] == 1 && M[0] == 0)
    Q[0] = 1, A[0] = 1;
  else if (Q[0] == 0 && M[0] == 1)
    Q[0] = 0, A[0] = 1;
  else
    Q[0] = 0, A[0] = 0;
}

void multiplicacao(int Q[BITS], int M[BITS], int A[BITS], int lenQ, int lenM)
{
  int i, cont, c = 0, sinal, maior;
  if ((Q[0] == 1 && M[0] == 0) || (Q[0] == 0 && M[0] == 1))
    sinal = 1;
  else
    sinal = 0;
  if (lenQ > lenM)
    cont = lenQ, maior = lenQ;
  else
    cont = lenM, maior = lenM;
  while (cont > 0)
  {
    c = 0;
    if (Q[BITS - 1] == 1)
    {
      c = somaMult(A, M, A, maior);
      c = deslocaDireita(A, c, maior);
      deslocaDireita(Q, c, maior);
    }
    else
    {
      c = deslocaDireita(A, c, maior);
      deslocaDireita(Q, c, maior);
    }

    cont--;
  }

  for (i = BITS - (maior + maior); i < BITS - maior; i++)
    A[i] = A[i + maior];
  for (i = BITS - (maior); i < BITS; i++)
    A[i] = Q[i];
  A[0] = sinal;
}

void zerarVetor(int *v)
{
  for (int i = 0; i < BITS; i++)
    v[i] = 0;
}

int verificaZero(int num[BITS])
{
  int contNum = 0;
  for (int i = 1; i < BITS; i++)
  {
    if (num[i] == 0)
      contNum++;
  }
  if (contNum == 15)
    return 1;
  else
    return 0;
}

int deslocaDireita(int num[BITS], int c, int len)
{
  int r, i;
  if (num[BITS - 1] == 1)
    r = 1;
  else
    r = 0;
  for (i = BITS - 1; i > BITS - len; i--)
  {
    num[i] = num[i - 1];
  }
  num[i] = c;
  return r;
}

int somaMult(int num1[BITS], int num2[BITS], int result[BITS], int len)
{
  int i, aux = 0;
  for (i = 15; i > 15 - len; i--)
    result[i] = somaBit(num1[i], num2[i], aux, &aux);
  return aux;
}

int menuSub(int num1[BITS], int num2[BITS], int result[BITS])
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
  {
    if (soma(num1, num2, result) == -1)
      return -1;
  }
  else if (num1[0] == 1 && num2[0] == 0) // -x - y
  {
    result[0] = 1;
    if (soma(num1, num2, result) == -1)
      return -1;
  }
  else if (num1[0] == 1 && num2[0] == 1) //-x -(-y)
  {
    if (x == 2)
      subtracao(num2, num1, result);
    else
      subtracao(num1, num2, result), result[0] = 1;
  }
}

int menuSoma(int num1[BITS], int num2[BITS], int result[BITS])
{
  if (num1[0] == 0 && num2[0] == 0) // x + y
  {
    if (soma(num1, num2, result) == -1)
      return -1;
  }
  else if (num1[0] == 0 && num2[0] == 1) // x + (-y)
    num2[0] = 0,
    menuSub(num1, num2, result);
  else if (num1[0] == 1 && num2[0] == 0) // -x + y
  {
    num1[0] = 0;
    int x = verificaMaior(num1, num2);
    menuSub(num1, num2, result);
    if (x == 1)
      result[0] = 1;
    else
      result[0] = 0;
  }
  else if (num1[0] == 1 && num2[0] == 1) // -x + (-y)
  {
    result[0] = 1;
    if (soma(num1, num2, result) == -1)
      return -1;
  }
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

int verificaMaiorSemSinal(int num1[BITS], int num2[BITS])
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

int somaBit(int b1, int b2, int b3, int *cout)
{
  *cout = (b1 + b2 + b3) / 2;
  return ((b1 + b2 + b3) % 2);
}

int soma(int num1[BITS], int num2[BITS], int result[BITS])
{
  int i, aux = 0;
  for (i = 15; i > 1; i--)
    result[i] = somaBit(num1[i], num2[i], aux, &aux);
  result[i] = aux;
  if (i == 1 && (num1[1] == 1 || num2[1] == 1))
    return -1;
  return aux;
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
  for (i = 15; i > 1; i--)
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

int converteBinario(int num, int vet[BITS])
{
  int i = BITS - 1, aux = num, cont = 0;
  if (num < 0)
    num = num * -1;

  while (num > 0)
  {
    if (num % 2 == 0)
      vet[i] = 0;
    else
      vet[i] = 1;
    num /= 2;
    i--;
    cont++;
  }
  if (aux < 0)
    vet[0] = 1;
  return cont;
}