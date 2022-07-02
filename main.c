#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "carta.h" // carta.h é o arquivo que contém as funções que manipulam as cartas
#include "jogo.h"
#include "lista.h"
#include "pilha.h"
#include "interface.h"
#include "save.h"

int main()
{
    // deixar o console com pelo menos 160 colunas

    pegarFullscreen() ? fullscreen() : mudarTamanhoJanela(160, 85);

    mudarFonte();

    inicializarAtributosPadrao();
    inicializarArquivosVetores();
    system("cls");
    aviso();
    menu(500);

    while (1)
    {
        chamarJogo(escolhaMenu());
        system("cls");
        menu(0);
    }

    return 0;
}
