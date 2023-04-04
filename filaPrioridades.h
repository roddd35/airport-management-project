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
        int removePriorityQueue(string idVoo, string idAviao, int index);
        int getElemento(int posicao);
        int removePlanes(int qtdAvioesRetirados, int *pista1, int *pista2, int *pista3, int tempoAtual, int *qtdOutroAeroporto, int *qtdPousos, int *qtdDecolagens, int *decolagensSemAtraso);
        void resizePriorityQueue();
        void insertPriorityQueue(Plane *x);
        void changePriority(int indice, int novapr);
        void adjustPriority(int tempoAtual);
        void writeQueue();
        void sobe(int i);
        void rebaixa(int i);
};