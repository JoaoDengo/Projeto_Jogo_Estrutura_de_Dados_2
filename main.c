#include <stdio.h>
#include <stdlib.h>
#include "itemTrunfo.h"

int main()
{
    srand(time(NULL));
    Lista *cartasJogador, *cartasBot;

    cartasJogador = criaListaVazia();
    cartasBot = criaListaVazia();

    printf("\n==== Super Trunfo de Super Carros ====\n");
    printf("Super Trunfo e um jogo de cartas onde os jogadores comparam atributos para vencer rodadas. Quem tiver o valor superior ganha a carta do adversario. O jogo continua ate um jogador ficar com todas as cartas.");
    insereFimLista(cartasJogador, 1, "Ferrari");
    insereFimLista(cartasJogador, 2, "Mustang");
    insereFimLista(cartasJogador, 3, "Camaro");
    insereFimLista(cartasJogador, 4, "McLaren");
    insereFimLista(cartasJogador, 5, "Bugatti");

    insereFimLista(cartasBot, 6, "Lamborghini");
    insereFimLista(cartasBot, 7, "Porsche");
    insereFimLista(cartasBot, 8, "Aston Martin");
    insereFimLista(cartasBot, 9, "Maserati");
    insereFimLista(cartasBot, 10, "Jaguar");

    jogarRodada(cartasJogador, cartasBot);
    printf("\n=== Minhas Cartas Finais ===\n");
    imprimeLista(cartasJogador);
    printf("\n=== Cartas Finais Bot ===\n");
    imprimeLista(cartasBot);

    liberarLista(cartasJogador);
    liberarLista(cartasBot);

    return 0;
}
