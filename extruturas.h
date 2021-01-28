/* 
 * File:   extruturas.h
 * Author: João Pedro
 *
 * Created on 4 de maio de 2020, 23:12
 */

#ifndef EXTRUTURAS_H
#define EXTRUTURAS_H

#define TD 0.05 //Taxa de disseminação
#define TI 0.2 //Taxa de imunidade

typedef struct sala local, *plocal;
    struct sala{
    int id; // id numérico do local
    int capacidade; // capacidade máxima
    int liga[3]; // id das ligações (-1 nos casos não usados)
};

typedef struct pessoa pessoa, *ppessoa;
    struct pessoa{
    char id[30]; // id alphanumérico da pessoa
    int idade; // cidade da pessoa
    char estado[2]; // id das ligações (-1 nos casos não usados)
    int dias;
    ppessoa prox;
};

#endif /* EXTRUTURAS_H */


