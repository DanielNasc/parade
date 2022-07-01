#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"
#include "interface.h"
#include "save.h"

int main()
{
    keybd_event(VK_MENU, 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

    inicializarArquivosVetores();
    system("cls");
    aviso();
    menu(500);
    chamarJogo(escolhaMenu());
    return 0;
}
