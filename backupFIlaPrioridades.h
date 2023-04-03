#pragma once

#include <iostream> 
#include <random>

using namespace std;

class Item {
    public:
        int elemento;
        int prioridade;
};

class PriorityQueue{
    private:
        Item *v;
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
        void insertPriorityQueue(Item x);
        void changePriority(int indice, int novapr);
        void sobe(int i);
        void rebaixa(int i);
};