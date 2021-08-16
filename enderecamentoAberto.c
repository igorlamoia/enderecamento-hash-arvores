#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// constante repesenta o tamanho da tabela
#define TAMANHO 100
#define QUANTIDADE 50
// Range de números aleatórios, tem que ser maior que a quantidade de números para não repetir
#define MIN 1
#define MAX 1000000

// estrutura Tabela com nome e uma matrícula
typedef struct
{
  int valor;
} Tabela;

// nossa tabela hash do tipo Tabela
Tabela tabelaHash[TAMANHO];

int contador = 0;
void menu();
// inicializa nossa tabela com o valor ZERO
void inicializarTabela();
// função de espalhamento (resto da divisão da chave por TAMANHO)
int funcaoHash(int chave);
// inserirLinear uma Tabela na tabela
void inserirLinear(int *numeros);
Tabela *buscar(int chave);
void imprimir();
Tabela lerTabela();
// Método Fisher–Yates shuffle, basicamente não deixa repetir números aleatórios
void aleatoriosNaoRepetidos(int *array);
// Tabela *buscarQuadratica(int chave);

int main()
{
  int opcao;
  Tabela *tab;
  double start, stop, elapsed;
  int *numeros = malloc((MAX - MIN) * sizeof(int));
  if (!numeros)
    exit(EXIT_FAILURE);

  do
  {
    for (int i = 0; i < MAX - MIN; i++)
    {
      numeros[i] = i + MIN;
    }
    aleatoriosNaoRepetidos(numeros);
    menu();
    scanf("%d", &opcao);
    // opcao = 2;
    srand(time(NULL));

    switch (opcao)
    {
    case 0:
      printf("Saindo...\n");
      break;
    case 1:
      inicializarTabela();

      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < QUANTIDADE; i++)
      {
        inserirLinear(numeros);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de insercao em segundos: %f\n\n\n", elapsed);
      contador = 0;
      break;
    case 2:
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < QUANTIDADE; i++)
      {
        tab = buscar(tabelaHash[i].valor);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de busca em segundos: %f\n\n\n", elapsed);
      break;
    case 3:
      imprimir();
      break;
    case 4:
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < TAMANHO; i++)
      {
        // tab = buscarQuadratica(tabelaHash[i].valor);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de busca Quadratica em segundos: %f\n\n\n", elapsed);
      break;
    default:
      printf("valor invalida!\n");
    }
  } while (opcao != 0);

  return 0;
}

void inicializarTabela()
{
  int i;
  for (i = 0; i < TAMANHO; i++)
    tabelaHash[i].valor = 0;
}

int funcaoHash(int chave)
{
  return chave % TAMANHO;
}

// função para ler e retornar uma Tabela
Tabela lerTabela(int *numeros)
{
  Tabela tab;
  tab.valor = numeros[contador];
  contador++;
  return tab;
}

void inserirLinear(int *numeros)
{
  Tabela tabela = lerTabela(numeros);
  int id = funcaoHash(tabela.valor);
  while (tabelaHash[id].valor)
    id = funcaoHash(id + 1);
  tabelaHash[id] = tabela;
}

Tabela *buscar(int chave)
{
  int id = funcaoHash(chave);
  while (tabelaHash[id].valor)
  {
    if (tabelaHash[id].valor == chave)
      return &tabelaHash[id];
    else
      id = funcaoHash(id + 1);
  }
  return NULL;
}

void imprimir()
{
  int i;
  printf("\n------------------------TABELA---------------------------\n");
  for (i = 0; i < TAMANHO; i++)
  {
    if (tabelaHash[i].valor)
      printf("%2d = %3d\n", i, tabelaHash[i].valor);
    else
      printf("%2d =\n", i);
  }
  printf("\n----------------------------------------------------------\n");
}

void menu()
{
  printf("\n-----Menu----\n");
  printf("1 - Inserir  |\n");
  printf("2 - Buscar   |\n");
  printf("3 - Imprimir |\n");
  printf("0 - Sair     |\n");
  printf("--------------\n");
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