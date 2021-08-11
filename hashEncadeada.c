#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 30 //Tamanho da lista (posições)
#define PRIMO 31
#define TAM 10 // Quantidade de números N

// Range de números aleatórios
#define MIN 1
#define MAX 200
// Quantidade de números aleatórios
#define QTDE 100000 //precisa ser menor que MAX

typedef struct no
{
  int chave;
  struct no *proximo;
} No;

typedef struct
{
  No *inicio;
  int tamanho;
} Lista;

void inicializarLista(Lista *lista);
void inserir_na_lista(Lista *lista, int valor);
int buscar_na_lista(Lista *lista, int valor);
void imprimir_lista(Lista *lista);
void inicializarTabela(Lista t[]);
void inserir(Lista lista[], int valor);
int busca(Lista lista[], int chave);
void imprimir(Lista lista[]);
int funcaoHash(int chave);
void shuffle(int *array);
void menu();

int main()
{
  int opcao, vetor[TAM];
  Lista tabela[TAMANHO];
  double start, stop, elapsed;
  inicializarTabela(tabela);
  int *numeros = malloc((MAX - MIN) * sizeof(int));
  if (!numeros)
    exit(EXIT_FAILURE);
  do
  {
    menu();
    scanf("%d", &opcao);
    srand(time(NULL));
    switch (opcao)
    {
    case 1:
      for (int i = 0; i < MAX - MIN; i++)
      {
        numeros[i] = i + MIN;
      }
      shuffle(numeros);
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i < TAM; i++)
      {
        inserir(tabela, numeros[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de insercao em segundos: %f\n\n\n", elapsed);
      // Buscando
      srand(time(NULL));
      for (int i = 0; i < TAM; i++)
      {
        busca(tabela, numeros[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\n\n\nTempo total de Busca em segundos: %f\n\n\n", elapsed);
      break;
    case 2:
      printf("VETOR:\n\n");
      printf("\n\nlista:");
      imprimir(&tabela);
    }
  } while (opcao != 3);
}

void menu()
{
  printf("\t\t\n-------------Menu-------------");
  printf("\t\t\n|1- Inserir                   |");
  printf("\t\t\n|2- Buscar                    |");
  printf("\t\t\n|3- Imprimir                  |");
  printf("\t\t\n|4- Sair                      |");
  printf("\t\t\n------------------------------\n\n");
}

void inicializarLista(Lista *lista)
{
  lista->inicio = NULL;
  lista->tamanho = 0;
}

void inserir_na_lista(Lista *lista, int valor)
{
  No *novo = malloc(sizeof(No));

  if (novo)
  {
    novo->chave = valor;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
  }
  else
    printf("\nErro na alocacao de memoria!\n");
}

int buscar_na_lista(Lista *lista, int valor)
{
  No *aux = lista->inicio;
  while (aux && aux->chave != valor)
    aux = aux->proximo;
  if (aux)
    return aux->chave;
  return 0; // Não encontrado
}

void imprimir_lista(Lista *lista)
{
  No *aux = lista->inicio;
  printf(" Tamanho: %d: ", lista->tamanho);
  while (aux)
  {
    printf("%d ", aux->chave);
    aux = aux->proximo;
  }
}

void inicializarTabela(Lista t[])
{
  int i;

  for (i = 0; i < TAMANHO; i++)
  {
    inicializarLista(&t[i]);
  }
}

void inserir(Lista lista[], int valor)
{
  int id = funcaoHash(valor);
  inserir_na_lista(&lista[id], valor);
}

int busca(Lista lista[], int chave)
{
  int id = funcaoHash(chave);
  // printf("\nIndice gerado, ao qual deveria estar na tabela: %d\n", id);
  return buscar_na_lista(&lista[id], chave);
}

void imprimir(Lista lista[])
{
  int i;
  for (i = 0; i < TAMANHO; i++)
  {
    printf("%2d = ", i);
    imprimir_lista(&lista[i]);
    printf("\n");
  }
}

int funcaoHash(int chave)
{
  return chave % PRIMO;
}

void shuffle(int *array)
{
  for (int i = MAX - MIN - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
  }
}