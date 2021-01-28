/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   leitura.h
 * Author: João Pedro
 *
 * Created on 9 de maio de 2020, 15:54
 */

#ifndef LEITURA_H
#define LEITURA_H

#ifdef __cplusplus
extern "C" {
#endif

ppessoa leituraPessoas(char *nomeF, ppessoa p);

void mostraPessoas(ppessoa p);

void listarLocais(char *nomeF);

local* adicionaLocal(local *tab, char *nomeF, int* numLocais);

void mostraLocais(plocal tab, int* numLocais);

void libertaLista(ppessoa p);

int verificaLicao(plocal tab, int* numLocais);

void criarFicheiroLocais(int count);

#ifdef __cplusplus
}
#endif

#endif /* LEITURA_H */

