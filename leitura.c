#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extruturas.h"

void libertaLista(ppessoa p){
    ppessoa aux;

    while(p != NULL){
        aux = p;
        p = p->prox;
        free(aux);
    }
}


void mostraPessoas(ppessoa p){
    if(p==NULL)
        printf("\nLista vazia\n");
    else{
        while( p != NULL){
            printf("\nIndetificador: %s",p->id);
            printf("\nIdade: %d",p->idade);
            printf("\nEstado: %s",p->estado);
            printf("\nDias Doente: %d\n",p->dias);
            p = p->prox;
        }
    }
}

ppessoa leituraPessoas(char *nomeF, ppessoa p){
    FILE *f;
    int c;
    ppessoa novo, aux;
    pessoa x;


    f = fopen(nomeF, "r");
    if(f == NULL){
        printf("\nErro a abrir ficheiro, por favor, tente novamente");
        return p;
    } 
    
    // Leitura de dados de cada pessoa e armazenamento temporário na variável x
    while ((fscanf(f," %29[^ ] %d %1[^ ]", x.id, &(x.idade), x.estado)) == 3)
    {
        if (strcmp(x.estado,"D") == 0)
            fscanf(f," %d", &(x.dias));
        else
            x.dias = 0;

        // Verficações de entrada

        if (x.idade < 0 || x.idade > 150)
        {
            printf("\nErro: Idade de %s invalida!", x.id);
            return NULL;
        }

        if ((strcmp(x.estado,"D") && strcmp(x.estado,"S") && strcmp(x.estado,"I")) != 0)
        {
            printf("\nErro: Estado de saude de %s invalido!", x.id);
            return NULL;
        }
        
        // Alocação de memória, penchimento e inserir bloco na lista

        novo = malloc(sizeof(pessoa));
        if(novo == NULL){
            printf("Erro na alocacao de memoria!");
            return p;
        }

        strncpy(novo->id, x.id, sizeof(x.id));
        strncpy(novo->estado, x.estado, sizeof(x.estado));
        novo->idade = x.idade;
        novo->dias = x.dias;
        novo->prox = NULL;

        if(p == NULL)       
            p = novo;
        else{
            aux = p;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = novo;
        } 
    }
    
    fclose(f);
    return p;
}


// -------------------- LOCAIS ---------------------------

void listarLocais(char *nomeF){
    FILE *f;
    local x;
    
    f = fopen(nomeF, "rb");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return;
    }
    
    while(fread(&x, sizeof(local), 1, f) == 1){
        printf("\nID: %d\nCapacidade: %d\nLigacoes: %d\t%d\t%d\n", x.id, x.capacidade, x.liga[0],x.liga[1],x.liga[2]);
    }
    fclose(f);
}

int verificaLicao(plocal tab, int* numLocais){
    // Falta otimizar o desempenho!!!!!!!!

    int aux = 0;

    for (int i = 0; i < *numLocais; i++) // Testa todos os locais
    {
        for (int k = 0; tab[i].liga[k] != -1 && k < 3; k++) // Testa cada ligação do bloco 
        {
            for (int j = 0; j < *numLocais; j++) // Percorre todos os elementos da lista à procura do bloco com o id da ligação anterior
            {
                if (tab[i].liga[k] == tab[j].id) // Econtra o bloco da ligação
                {
                    for (int g = 0; tab[j].liga[g] != -1 && g < 3 ; g++) //Procura o id do local que está a ser testado
                    {
                        if (tab[j].liga[g] == tab[i].id) // Encontra o id do local original no local de ligação
                        {
                            aux = 1;
                            break;
                        }
                        else
                            aux = 0;
                    }
                    break;
                }
                
            }  
        }
    }

    // Caso o aux permaneça a zero, significa que houve uma ligação que não estavam iterligadas entre si
    if (aux)
        return 1;
    return 0;
}

plocal adicionaLocal(plocal tab, char *nomeF, int* numLocais){
    FILE *f;
    local x;
    int count = 0;
    
    // Abertura do ficheiro
    f = fopen(nomeF, "rb");
    if(f==NULL){
        printf("Erro no acesso ao ficheiro\n");
        return NULL;
    }

    // Obter Número de clientes e espaço em memória para todos
    fseek(f, 0, SEEK_END);
    *numLocais = ftell(f)/sizeof(local);
    rewind(f);
    tab = malloc(sizeof(local) * *numLocais);
    if(tab == NULL){
        printf("Erro na Alocacao de memoria\n");
        fclose(f);
        return NULL;
    }

    // Ciclo de leitura e escrita para o vetor dinâmico
    while(fread(&x, sizeof(local), 1, f) == 1 && count < *numLocais){
        tab[count].id = x.id;
        tab[count].capacidade = x.capacidade;
        for (int i = 0; i < 3; i++)
            tab[count].liga[i] = x.liga[i];
        
        // Validação de Parâmetros de entrada
        
        if (x.id < 0 && x.id != -1)
        {
            printf("\nErro: O Id do local %d e invalido!", x.id);
            free(tab);
            return NULL;
        }
        for (int i = 0; i < count; i++)
        {
            if (tab[i].id == x.id)
            {
                printf("\nErro: O Id do local %d esta repetido!", x.id);
                free(tab);
                return NULL;
            } 
        }
        count++;
    }

    if((verificaLicao(tab, numLocais)) == 0){
       printf("\nErro: Ligacoes invalidas");
                free(tab);
                return NULL; 
    }

    fclose(f);
    return tab;
}

void mostraLocais(plocal tab, int* numLocais){
    printf("\n------ Locais ------\n");
    for (int i = 0; i < *numLocais; i++)
        printf("\nID: %d\nCapacidade: %d\nLigacoes: %d\t%d\t%d\n", tab[i].id, tab[i].capacidade, tab[i].liga[0],tab[i].liga[1],tab[i].liga[2]);  
}

void criarFicheiroLocais(int count){
    FILE *f;
    local x;

    for (int i = 0; i < count; i++)
    {
        printf("\nId: ");
        scanf("%d", &x.id);
        printf("\nCapacidade: ");
        scanf("%d", &x.capacidade);
        printf("\nLigacoes: ");
        scanf("%d %d %d", &x.liga[0], &x.liga[1], &x.liga[2]);

        f = fopen("test.bin", "wb");
        if (f == NULL)
        {
            printf("\nErro a criar ficheiro de testes!");
            return;
        }

        fwrite(&x, sizeof(local), 1, f);
    }

    fclose(f);
    return;
}
