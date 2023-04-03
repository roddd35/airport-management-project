#pragma once

#include "aviao.h"

#include <iostream> 
#include <random>

using namespace std;

class PriorityQueue{
    private:
        Plane *v;
        int *indice;
        int n;          // quantidade de itens na fila
        int max;        // capacidade da fila
        int tamanho;

    public:
        PriorityQueue(int max, int tam);
        ~PriorityQueue();
        int isEmpty();
        int removePriorityQueue();
        int getElemento(int posicao);
        void resizePriorityQueue();
        void insertPriorityQueue(Plane *x);
        void changePriority(int indice, int novapr);
        void writeQueue();
        void sobe(int i);
        void rebaixa(int i);
};