#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// constante repesenta o tamanho da tabela
#define TAMANHO 200000
#define QUANTIDADE 100000
// Range de números aleatórios, tem que ser maior que a quantidade de números para não repetir
#define MIN 1
#define MAX 10000000

// estrutura Tabela com nome e uma matrícula
typedef struct
{
  int valor;
} Tabela;

// nossa tabela hash do tipo Tabela
Tabela tabelaHash[TAMANHO];

// inicializa nossa tabela com o valor de codigo -1
void inicializarTabela()
{
  int i;
  for (i = 0; i < TAMANHO; i++)
    tabelaHash[i].valor = -1;
}
// Método Fisher–Yates shuffle, basicamente não deixa repetir números aleatórios
void aleatoriosNaoRepetidos(int *array);
// função de espalhamento (resto da divisão da chave por TAMANHO)
int gerarCodigoHash(int chave)
{
  return chave % TAMANHO;
}

// inserir uma pessoa na tabela
void inserir(int chave)
{
  Tabela tab;
  tab.valor = chave;
  int indice = gerarCodigoHash(tab.valor);
  while (tabelaHash[indice].valor != -1)
    indice = gerarCodigoHash(indice + 1);
  tabelaHash[indice] = tab;
}

Tabela *buscar(int chave)
{
  int indice = gerarCodigoHash(chave);
  while (tabelaHash[indice].valor != -1)
  {
    if (tabelaHash[indice].valor == chave)
      return &tabelaHash[indice];
    else
      indice = gerarCodigoHash(indice + 1);
  }
  return NULL;
}

void imprimir()
{
  int i;
  printf("\n------------------------TABELA---------------------------\n");
  for (i = 0; i < TAMANHO; i++)
  {
    if (tabelaHash[i].valor != -1)
      printf("%2d = %3d\n", i, tabelaHash[i].valor);
    else
      printf("%2d =\n", i);
  }
  printf("\n----------------------------------------------------------\n");
}

int main()
{
  int op, chave, quantidade;
  Tabela *tab;
  double start, stop, elapsed;
  int *numeros = malloc((MAX - MIN) * sizeof(int));
  if (!numeros)
    exit(EXIT_FAILURE);

  inicializarTabela(); // com -1

  // inicializa vetor número
  for (int i = 0; i < MAX - MIN; i++)
    numeros[i] = i + MIN;

  aleatoriosNaoRepetidos(numeros);

  do
  {
    printf("1 - Inserir\n2 - Buscar\n3 - Imprimir\n0 - Sair\n");
    scanf("%d", &op);

    switch (op)
    {
    case 0:
      printf("Saindo...\n");
      break;
    case 1:
      // printf("Digite a quantidade de numeros aleatorios que devem ser inseridos:\n");
      // scanf("%d", &quantidade);
      // if (quantidade > TAMANHO || 0 > quantidade)
      // {
      //   printf("Digite um valor entre 1 e %d\n", TAMANHO);
      //   break;
      // }
      srand(time(NULL));
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < QUANTIDADE; i++)
      {
        // scanf("%d", &chave);
        // inserir(chave);
        inserir(numeros[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de insercao em segundos: %f\n\n\n", elapsed);
      break;
    case 2:
      srand(time(NULL));
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < QUANTIDADE; i++)
      {
        // scanf("%d", &chave);
        // inserir(chave);
        tab = buscar(numeros[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de Busca em segundos: %f\n\n\n", elapsed);
      break;
    case 3:
      imprimir();
      break;
    default:
      printf("Opcao invalida!\n");
    }

  } while (op != 0);

  return 0;
}

void aleatoriosNaoRepetidos(int *array)
{
  for (int i = MAX - MIN - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
  }
}