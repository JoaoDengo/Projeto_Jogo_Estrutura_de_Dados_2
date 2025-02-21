#include <stdio.h>
#include <stdlib.h>
#include "itemTrunfo.h"
#define VERDE "\033[0;32m"
#define AZUL    "\x1b[34m"
#define VERMELHO     "\x1b[31m"
#define RESET "\033[0m"
#define AMARELO "\033[0;33m"



struct item
{
    int chave;
    char nome[100];
    int kmFinal;
    int hp;
    float tempo0_100;
    int qtdCilindros;
    float kg;
};

struct celula
{
    Item item;
    Celula *prox;
};

struct lista
{
    Celula *primeira;
};

Lista * criaListaVazia()
{
    Lista *lst = malloc(sizeof(Lista));
    lst->primeira = NULL;
    return lst;
}

int verificaListaVazia(Lista *lst)
{
    return lst->primeira == NULL;
}

void gerarValoresAleatorios(Item *item)
{
    item->kmFinal = rand() % 101 + 180;
    item->hp = rand() % 801 + 400;
    item->tempo0_100 = (rand() % 50) / 20.0 + 2.0;
    item->qtdCilindros = (rand() % 6) +4;
    item->kg = (rand() % 2000) + 800;
}

void imprimeLista(Lista *lst)
{
    Celula *aux;
    int i = 1;

    for(aux = lst->primeira; aux != NULL; aux = aux->prox)
    {
        printf(AZUL"\n==============================================\n"RESET);
        printf(AZUL"|                CARTA %d                  \n"RESET, i);
        printf(AZUL"==============================================\n"RESET);

        printf(AMARELO"| Chave: "VERDE"%d                           \n"RESET, aux->item.chave);
        printf(VERMELHO"| Nome do Carro: "VERDE"%-40s \n" RESET, aux->item.nome);
        printf(VERMELHO"| KM Final: "VERDE"%10d                           \n" RESET, aux->item.kmFinal);
        printf(VERMELHO"| Cavalos (HP): "VERDE"%9d                         \n"RESET, aux->item.hp);
        printf(VERMELHO"| Tempo 0-100 km/h: "VERDE"%6.2f s                 \n"RESET, aux->item.tempo0_100);
        printf(VERMELHO"| Quantidade de Cilindros: "VERDE"%6d              \n"RESET, aux->item.qtdCilindros);
        printf(VERMELHO"| Peso: "VERDE"%10.2f kg                          \n"RESET, aux->item.kg);

        printf(AZUL"==============================================\n"RESET);
        i++;
    }
}

void insereFimLista(Lista *lst, int chave, char *nome)
{
    Item novo;
    novo.chave = chave;
    Celula *nova = malloc(sizeof(Celula));

    strcpy(nova->item.nome, nome);
    nova->item.chave = chave;

    gerarValoresAleatorios(&nova->item);
    nova->prox = NULL;

    if(verificaListaVazia(lst))
    {
        lst->primeira = nova;
    }
    else
    {
        Celula *ultima = lst->primeira;
        while(ultima->prox != NULL)
        {
            ultima = ultima->prox;
        }
        ultima->prox = nova;
    }
}

void removeItem(Lista *lst, int chave)
{
    printf("Tentando remover carta com chave %d...\n", chave);

    Celula *aux = lst->primeira;
    Celula *anterior = NULL;

    while (aux != NULL && aux->item.chave != chave)
    {
        anterior = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        printf("Item não encontrado! Chave: %d\n", chave);
        return;
    }

    if (anterior == NULL)
    {
        lst->primeira = aux->prox;
    }
    else
    {
        anterior->prox = aux->prox;
    }

    free(aux);
    printf("Carta com chave %d removida com sucesso!\n", chave);
}

void liberarLista(Lista *lst)
{
    Celula *aux = lst->primeira;
    Celula *liberar;
    while(aux != NULL)
    {
        liberar = aux;
        aux = aux->prox;
        free(liberar);
    }
    free(lst);
}

int tamanhoLista(Lista *lst)
{
    int tamanho = 0;
    Celula *aux = lst->primeira;

    while (aux != NULL)
    {
        tamanho++;
        aux = aux->prox;
    }

    return tamanho;
}


Celula *buscaPorChave(Lista *lst, int chave)
{
    Celula *aux = lst->primeira;
    while (aux != NULL && aux->item.chave != chave)
    {
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        printf("Item com chave %d nao encontrado na lista.\n", chave);
    }

    return aux;
}





void jogarRodada(Lista *cartasJogador, Lista *cartasBot)
{
    if (verificaListaVazia(cartasJogador) || verificaListaVazia(cartasBot))
    {
        printf("Fim do jogo! Uma das listas está vazia.\n");
        return;
    }

    while(verificaListaVazia(cartasJogador) != 1 && verificaListaVazia(cartasBot) != 1)
    {
        printf(AMARELO"\n\n=== Suas Cartas ===" RESET);
        imprimeLista(cartasJogador);

        int escolhaCartaJogador;
        Celula *cartaJogadorCelula = NULL;

        do
        {
            printf("\nEscolha a carta que deseja jogar " AMARELO "(digite a chave do carro): " RESET);
            scanf("%d", &escolhaCartaJogador);

            cartaJogadorCelula = buscaPorChave(cartasJogador, escolhaCartaJogador);

            if (cartaJogadorCelula == NULL)
            {
                printf("\nChave invalida! Por favor, escolha uma chave existente.\n");
            }
        } while (cartaJogadorCelula == NULL);


        Item carroJogador = cartaJogadorCelula->item;
        printf(VERDE"\nVoce escolheu: "RESET AMARELO"%s" RESET"(HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n",
               carroJogador.nome, carroJogador.hp, carroJogador.kmFinal, carroJogador.tempo0_100, carroJogador.qtdCilindros, carroJogador.kg);

        int escolhaJogador;
        do{
            printf("\nEscolha um atributo para comparar:\n");
            printf("1 - HP\n");
            printf("2 - KM Final\n");
            printf("3 - Tempo 0-100\n");
            printf("4 - Quantidade de Cilindros\n");
            printf("5 - Peso\n");
            printf("Digite a opcao: ");
            scanf("%d", &escolhaJogador);

            if(escolhaJogador < 1 || escolhaJogador > 5){
                printf(VERMELHO"\nEscolha uma opcao valida\n"RESET);
            }

        }while(escolhaJogador < 1 || escolhaJogador > 5);

        printf("\n== COMPARACAO ===\n");

        printf(VERDE"\nVoce escolheu: %s (HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n" RESET,
               carroJogador.nome, carroJogador.hp, carroJogador.kmFinal, carroJogador.tempo0_100, carroJogador.qtdCilindros, carroJogador.kg);

        int tamanhoBot = tamanhoLista(cartasBot);

        int escolhaCartaBotIndex = rand() % tamanhoBot;

        Celula *cartaBotCelula = cartasBot->primeira;
        for (int i = 0; i < escolhaCartaBotIndex; i++)
        {
            if (cartaBotCelula != NULL)
                cartaBotCelula = cartaBotCelula->prox;
        }

        if (cartaBotCelula == NULL)
        {
            printf("Erro: Carta do bot não encontrada!\n");
            return;
        }

        Item carroBot = cartaBotCelula->item;

        printf(VERMELHO"\nCarta do Bot: %s (HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n" RESET,
               carroBot.nome, carroBot.hp, carroBot.kmFinal, carroBot.tempo0_100, carroBot.qtdCilindros, carroBot.kg);
        sleep(3);
        int vencedor = 0;

        switch (escolhaJogador)
        {
        case 1:
            if (carroJogador.hp > carroBot.hp) vencedor = 1;
            else if (carroJogador.hp < carroBot.hp) vencedor = 2;
            break;
        case 2:
            if (carroJogador.kmFinal > carroBot.kmFinal) vencedor = 1;
            else if (carroJogador.kmFinal < carroBot.kmFinal) vencedor = 2;
            break;
        case 3:
            if (carroJogador.tempo0_100 < carroBot.tempo0_100) vencedor = 1;
            else if (carroJogador.tempo0_100 > carroBot.tempo0_100) vencedor = 2;
            break;
        case 4:
            if (carroJogador.qtdCilindros > carroBot.qtdCilindros) vencedor = 1;
            else if (carroJogador.qtdCilindros < carroBot.qtdCilindros) vencedor = 2;
            break;
        case 5:
            if (carroJogador.kg > carroBot.kg) vencedor = 1;
            else if (carroJogador.kg < carroBot.kg) vencedor = 2;
            break;
        default:
            printf("Escolha invalida! Rodada cancelada.\n");
            return;
        }

        if (vencedor == 1)
        {
            printf(VERDE"\nVoce venceu a rodada!\n"RESET);
            insereFimLista(cartasJogador, carroBot.chave, carroBot.nome);
            removeItem(cartasBot, carroBot.chave);
        }
        else if (vencedor == 2)
        {
            printf(VERMELHO"\nBot venceu a rodada!\n"RESET);
            insereFimLista(cartasBot, carroJogador.chave, carroJogador.nome);
            removeItem(cartasJogador, carroJogador.chave);
        }
        else
        {
            printf("\nEmpate! Nenhuma carta foi movida.\n");
        }
        sleep(5);

        if (cartaJogadorCelula != NULL && cartaBotCelula != NULL)
        {
            carroJogador = cartaJogadorCelula->item;
            carroBot = cartaBotCelula->item;
        }
        else
        {
            printf("Fim de jogo! Nao ha mais cartas para jogar.\n");
            return;
        }

      //rodada do bot -------------------------------------------------
        tamanhoBot = tamanhoLista(cartasBot);

        escolhaCartaBotIndex = rand() % tamanhoBot;

        cartaBotCelula = cartasBot->primeira;
        for (int i = 0; i < escolhaCartaBotIndex; i++)
        {
            if (cartaBotCelula != NULL)
                cartaBotCelula = cartaBotCelula->prox;
        }

        if (cartaBotCelula == NULL)
        {
            printf("Erro: Carta do bot não encontrada!\n");
            return;
        }

        carroBot = cartaBotCelula->item;

        printf(AMARELO"\n\n====== Rodada do Bot ======\n"RESET);
        printf(VERDE"\n=== Suas Cartas ===\n"RESET);
        imprimeLista(cartasJogador);

        int escolhaCartaJogadorBot;
        do
        {
            printf("\nEscolha a carta que deseja jogar " AMARELO "(digite a chave do carro): " RESET);
            scanf("%d", &escolhaCartaJogadorBot);

            cartaJogadorCelula = buscaPorChave(cartasJogador, escolhaCartaJogadorBot);

            if (cartaJogadorCelula == NULL)
            {
                printf("\nChave invalida! Por favor, escolha uma chave existente.\n");
            }
        } while (cartaJogadorCelula == NULL);

        carroJogador = cartaJogadorCelula->item;
        printf("\nVoce escolheu: %s (HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n",
               carroJogador.nome, carroJogador.hp, carroJogador.kmFinal, carroJogador.tempo0_100, carroJogador.qtdCilindros, carroJogador.kg);

        carroJogador = cartaJogadorCelula->item;

        printf("\nAguarde o Bot Jogar...\n");
        sleep(3);

        printf("1 - HP\n");
        printf("2 - KM Final\n");
        printf("3 - Tempo 0-100\n");
        printf("4 - Quantidade de Cilindros\n");
        printf("5 - Peso\n");
        int escolhaBot = rand() % 5 + 1;
        printf("Bot escolheu o atributo %d\n", escolhaBot);


        printf("\n--- COMPARACAO ---\n");
        printf(VERDE"Sua Carta: %s (HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n"RESET,
               carroJogador.nome, carroJogador.hp, carroJogador.kmFinal, carroJogador.tempo0_100, carroJogador.qtdCilindros, carroJogador.kg);

        printf(VERMELHO"Carta do Bot: %s (HP: %d, KM Final: %d, 0-100: %.2f, Quantidade Cilindros: %d, Peso: %.2f)\n"RESET,
               carroBot.nome, carroBot.hp, carroBot.kmFinal, carroBot.tempo0_100, carroBot.qtdCilindros, carroBot.kg);

        sleep(5);

        vencedor = 0;
        switch (escolhaBot)
        {
        case 1:
            if (carroBot.hp > carroJogador.hp) vencedor = 2;
            else if (carroBot.hp < carroJogador.hp) vencedor = 1;
            break;
        case 2:
            if (carroBot.kmFinal > carroJogador.kmFinal) vencedor = 2;
            else if (carroBot.kmFinal < carroJogador.kmFinal) vencedor = 1;
            break;
        case 3:
            if (carroBot.tempo0_100 < carroJogador.tempo0_100) vencedor = 2;
            else if (carroBot.tempo0_100 > carroJogador.tempo0_100) vencedor = 1;
            break;
        case 4:
            if (carroBot.qtdCilindros > carroJogador.qtdCilindros) vencedor = 2;
            else if (carroBot.qtdCilindros < carroJogador.qtdCilindros) vencedor = 1;
            break;
        case 5:
            if (carroBot.kg > carroJogador.kg) vencedor = 2;
            else if (carroBot.kg < carroJogador.kg) vencedor = 1;
            break;
        default:
            break;
        }

        if (vencedor == 2)
        {
            printf(VERMELHO"\nBot venceu a rodada!\n"RESET);
            insereFimLista(cartasBot, carroJogador.chave, carroJogador.nome);
            removeItem(cartasJogador, carroJogador.chave);
            sleep(3);
        }
        else if (vencedor == 1)
        {
            printf(VERDE"\nVoce venceu a rodada!\n"RESET);
            insereFimLista(cartasJogador, carroBot.chave, carroBot.nome);
            removeItem(cartasBot, carroBot.chave);
            sleep(3);
        }
        else
        {
            printf("\nEmpate! Nenhuma carta foi movida.\n");
        }

        cartaJogadorCelula = cartasJogador->primeira;
        cartaBotCelula = cartasBot->primeira;
    }
}
