#ifndef ITEMTRUNFO_H_INCLUDED
#define ITEMTRUNFO_H_INCLUDED

typedef struct item Item;
typedef struct lista Lista;
typedef struct celula Celula;

Lista * criaListaVazia();
int verificaListaVazia(Lista *lst);
void gerarValoresAleatorios(Item *item);
void imprimeLista(Lista *lst);
void insereFimLista(Lista *lst, int chave, char *nome);
Celula * buscaPorChave(Lista *lst, int chave);
void removeItem(Lista *lst, int x);
void liberarLista(Lista *lst);
void jogarRodada(Lista *cartasJogador, Lista *cartasBot);
int tamanhoLista(Lista *lst);

#endif // ITEMTRUNFO_H_INCLUDED
