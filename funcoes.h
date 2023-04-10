#pragma once

#include <iostream>
#include <string>
#include <random>

#include "filaPrioridades.h"
#include "aviao.h"

using namespace std;

// PROTÓTIPO DAS FUNÇÕES
int decideEmergencia(int probEmergencia);
int decideMaxCombustivel(int tempoCombustivel);
int decideMaxDecolagem(int tempoVoo);
void imprimeEstatisticas(int totalAvioes, int totalEmergencia, int qtdDecolagens, int totalDecolagensSemAtraso, int qtdPousos, int qtdOutroAeroporto, int emergenciasAtendidas);
void leituraEntrada(int *tempoTotal, int *qtdAvioes, int *probPouso, int *probEmergencia, int *probDecolagem, int *tempoCombustivel, int *tempoVoo);
void execucao(int tempoTotal, int qtdAvioes, int probPouso, int probEmergencia, int probDecolagem, int tempoCombustivel, int tempoVoo, int qtdAvioesRetirados);
char decideAcao(int probPouso);
string geradorIdVoo();
string geradorIdAviao();