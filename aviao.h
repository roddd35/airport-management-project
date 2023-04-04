#pragma once

#include <iostream> 
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Plane {
    protected:
        // o tempo limite é definido por TEMPO ATUAL + COMBUSTIVEL INICIAL
        int combustivel;
        int tempoEspera;    // tempo maximo que um avião pode esperar até sair da fila OBS: adicionar tolerancia de 10% para decolagens
        int Emergencia;     // decidir aleatoriamente, se for 1 é emergência, senão não
        int prioridade;
        int atraso = 0;
        char acao;          // Pouso (p) ou Decolagem (d)
        string idVoo;       // origem ou destino, a depender se é pouso ou decolagem 3 digitos
        string idAviao;     // 2 letras (empresa) e 3 números (numero do voo)

    public:
        Plane(int c, int TL, int E, int p, char a, string idV, string idA);
        ~Plane();
        Plane() = default;
        int getCombustivel();
        int getTempoEspera();
        int getPrioridade();
        int getAtraso();
        char getAcao();
        void setPrioridade(int novapr);
        void aumentaTempoEspera();
        void gastaCombustivel();
        string getIdAviao();
        string getIdVoo();
};