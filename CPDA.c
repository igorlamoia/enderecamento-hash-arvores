#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000 // Quantidade de números N dentro da lista

// Range de números aleatórios, tem que ser maior que a quantidade de números para não repetir
#define MIN 1
#define MAX 100000

typedef struct NO
{
  int info;
  struct NO *esq;
  struct NO *dir;
} Arvore;

void menu();
Arvore *insereNumeros(Arvore *Arv, int info);
Arvore *removeNumeros(Arvore *Arv, int chave);
int buscar(Arvore *Arv, int v);
void InOrder(Arvore *Arv);
void embaralhaNumeros(int *array);

int main()
{
  Arvore *minhaArvore = NULL;
  int aleatorio[TAM], opcao = 0, n, v;
  double start, stop, elapsed;
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
      system("cls");
      printf("Digite o numero de Elementos desejados: ");
      scanf("%d", &n);
      if (n >= 1 && n <= TAM)
      {
        // Inicializa vetor com valores crescentes, pra depois os embaralhar aleatóriamente
        for (int i = 0; i < MAX - MIN; i++)
          numeros[i] = i + MIN;

        embaralhaNumeros(numeros);

        start = (double)clock() / CLOCKS_PER_SEC;
        for (int i = 0; i < n; i++)
        {
          aleatorio[i] = numeros[i];
          minhaArvore = insereNumeros(minhaArvore, aleatorio[i]);
        }
        printf("\nAB criada com sucesso!\n");
        stop = (double)clock() / CLOCKS_PER_SEC;
        elapsed = stop - start;
        printf("\nTempo total em segundos para insercao: %f segundos\n", elapsed);
        system("pause>>null");
      }
      else
      {
        printf("\nPor favor, digite um valor entre 1 e 100.000");
      }
      system("pause>>null");
      break;
    case 2:
      system("cls");
      printf("Digite o numero de Elementos que deseja remover: ");
      scanf("%d", &n);
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i <= n; i++)
      {
        minhaArvore = removeNumeros(minhaArvore, aleatorio[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\nAB excluida com sucesso!\n");
      printf("\nTempo total em segundos para exclusao de todos elementos e de: %f segundos\n", elapsed);
      system("pause>>null");
      break;
    case 3:
      system("cls");
      start = (double)clock() / CLOCKS_PER_SEC;
      for (int i = 0; i <= n; i++)
      {
        buscar(minhaArvore, aleatorio[i]);
      }
      stop = (double)clock() / CLOCKS_PER_SEC;
      elapsed = stop - start;
      printf("\nTempo total de busca foi de: %f segundos\n", elapsed);
      system("pause>>null");
      break;
    case 4:
      system("cls");
      InOrder(minhaArvore);
      system("pause>>null");
      break;
    }
  } while (opcao != 5);
  return 0;
}

Arvore *insereNumeros(Arvore *Arv, int info)
{
  //Caso a �rvore esteja vazia.
  if (Arv == NULL)
  {
    Arv = (Arvore *)malloc(sizeof(Arvore)); //Aloca mem�ria para a �rvore
    Arv->info = info;
    Arv->esq = NULL;
    Arv->dir = NULL;
  }
  else
  {
    if (info < Arv->info)
      Arv->esq = insereNumeros(Arv->esq, info);
    else if (info > Arv->info)
      Arv->dir = insereNumeros(Arv->dir, info);
  }

  return Arv;
}

Arvore *removeNumeros(Arvore *Arv, int chave)
{
  if (Arv == NULL)
    return NULL;
  else if (Arv->info > chave)
    Arv->esq = removeNumeros(Arv->esq, chave);
  else if (Arv->info < chave)
    Arv->dir = removeNumeros(Arv->dir, chave);
  else
  { /* achou o n� a remover */
    /* n� sem filhos */
    if (Arv->esq == NULL && Arv->dir == NULL)
    {
      free(Arv);
      Arv = NULL;
    }
    /* n� s� tem filho � direita */
    else if (Arv->esq == NULL)
    {
      Arvore *t = Arv;
      Arv = Arv->dir;
      free(t);
    }
    /* s� tem filho � esquerda */
    else if (Arv->dir == NULL)
    {
      Arvore *t = Arv;
      Arv = Arv->esq;
      free(t);
    }
    /* n� tem os dois filhos */
    else
    {
      Arvore *f = Arv->esq;
      while (f->dir != NULL)
      {
        f = f->dir;
      }
      Arv->info = f->info; /* troca as informa��es */
      f->info = chave;
      Arv->esq = removeNumeros(Arv->esq, chave);
    }
  }
  return Arv;
}

int buscar(Arvore *Arv, int chave)
{
  if (Arv == NULL)
  {
    return 0;
  }
  else if (chave < Arv->info)
  {
    return buscar(Arv->esq, chave);
  }
  else if (chave > Arv->info)
  {
    return buscar(Arv->dir, chave);
  }
  else
  {
    return 1;
  }
}

void InOrder(Arvore *Arv)
{ //Imprime os valores da �rvore em �rdem crescente.
  if (Arv != NULL)
  {
    InOrder(Arv->esq);
    printf("%d ", Arv->info);
    InOrder(Arv->dir);
  }
}

void menu()
{
  system("cls");
  printf("\n----------------MENU PRINCIPAL----------------");
  printf("\n 1 - Criar AB Aleatoria com N numeros - Limite de 100.000 Elementos");
  printf("\n 2 - Remover N Elementos Aleatorios da AB - Limite de 100.000 Elementos");
  printf("\n 3 - Buscar todos os Elementos da AB");
  printf("\n 4 - Exibir a AB em ordem");
  printf("\n 5 - Encerrar");
  printf("\n\n Opcao Escolhida: \n");
}
void embaralhaNumeros(int *array)
{
  for (int i = MAX - MIN - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
  }
}