/* 
 * File:   main.c
 * Author: João Pedro
 * Created on 4 de maio de 2020, 22:51
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "extruturas.h"
#include "leitura.h"


int main(int argc, char** argv) {
    ppessoa x = NULL;
    plocal y = NULL;
    int numLocais = 0;

    /* criarFicheiroLocais(3);
    return 0; */

    x = leituraPessoas("pessoasA.txt", x);
    mostraPessoas(x);
    /* printf("\n---- Locais 1 ----\n");
    listarLocais("test.bin"); */
    y = adicionaLocal(y,"E1.bin", &numLocais);
    /* printf("\n---- Locais 2 ----\n"); */
    mostraLocais(y, &numLocais);

    mostraMenu();
    // Libertar memória
    free(y);
    libertaLista(x);

    return (EXIT_SUCCESS);
}
