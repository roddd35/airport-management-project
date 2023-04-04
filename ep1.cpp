#include "funcoes.h"

// FUNÇÃO MAIN
int main(){
    int tempoTotal;
    int qtdAvioes;
    int probPouso;
    int probDecolagem;
    int probEmergencia;
    int tempoCombustivel;
    int tempoVoo;
    int qtdAvioesRetirados = 0;

    cout << "-*-*- Bem Vinde ao Simulador de Aeroporto! -*-*-" << endl;
    cout << "Por favor, preencha os dados abaixo!" << endl << endl;

    leituraEntrada(&tempoTotal, &qtdAvioes, &probPouso, &probEmergencia, &probDecolagem, &tempoCombustivel, &tempoVoo);    
    execucao(tempoTotal, qtdAvioes, probPouso, probEmergencia, probDecolagem, tempoCombustivel, tempoVoo, qtdAvioesRetirados);

    cout << endl << "Obrigado por utilizar o nosso serviço!" << endl;
    
    return 0;
}