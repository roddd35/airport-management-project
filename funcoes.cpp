#include "funcoes.h"

// FUNÇÕES
void leituraEntrada(int *tempoTotal, int *qtdAvioes, int *probPouso, int *probEmergencia, int *probDecolagem, int *tempoCombustivel, int *tempoVoo){
    cout  << "Digite a duração da simulação: ";
    cin >> *tempoTotal;

    cout << "Digite o número de aviões que chegam no aeroporto: ";
    cin >> *qtdAvioes;

    cout << "Digite a probabilidade de ser pouso (0-100): ";
    cin >> *probPouso;
    *probDecolagem = 100 - *probPouso;

    cout << "Digite a probabilidade de ser emergência (0-100): ";   // ideia: o valor seja baixo
    cin >> *probEmergencia; 

    cout << "Digite o tempo máximo de combustível de um avião: ";
    cin >> *tempoCombustivel;

    cout << "Digite o tempo máximo de voo de um avião: ";
    cin >> *tempoVoo;
}

void execucao(int tempoTotal, int qtdAvioes, int probPouso, int probEmergencia, int probDecolagem, int tempoCombustivel, int tempoVoo, int qtdAvioesRetirados){
    int pista1 = 0, pista2 = 0, pista3 = 0; // sobe para dois a cada vez que for usada e só pode ser usada quando seu valor for 0
    int decisaoEmergencia;
    int prioridade;
    int combustivel;
    int tempoEspera;
    int totalDecolagensSemAtraso = 0;
    int qtdOutroAeroporto = 0;
    int qtdPousos = 0;
    int qtdDecolagens = 0;
    char decisaoAcao;
    string idAviao;
    string idVoo;

    PriorityQueue *fila = new PriorityQueue(1, 255);

    for(int i = 0; i < tempoTotal; i++){ 
        cout << endl << "-*- Turno Atual: " << i + 1 << " -*-" << endl;
        // criar os objetos do avião
        for(int j = 0; j < qtdAvioes + 1; j++){
            decisaoEmergencia = decideEmergencia(probEmergencia);
            decisaoAcao = decideAcao(probPouso);
            idAviao = geradorIdAviao();
            idVoo = geradorIdVoo();
            //  cria um avião de pouso
            if(decisaoAcao == 'p'){
                combustivel = decideMaxCombustivel(tempoCombustivel);
                tempoEspera = 0; 
            }
            //  cria um avião de decolagem
            else{
                combustivel = 0;
                tempoEspera = decideMaxDecolagem(tempoVoo);
            }
            if(decisaoEmergencia == 1 && decisaoAcao != 'd')
                prioridade = 4; // maior prioridade
            else
                prioridade = 1;
            Plane *aviao = new Plane(combustivel, tempoEspera + i, decisaoEmergencia, prioridade, decisaoAcao, idVoo, idAviao);
            fila->insertPriorityQueue(aviao);
        }
        qtdAvioesRetirados = fila->removePlanes(qtdAvioesRetirados, &pista1, &pista2, &pista3, i, &qtdOutroAeroporto, &qtdPousos, &qtdDecolagens, &totalDecolagensSemAtraso);
        cout << endl << "Nesse turno, o total de pousos ou decolagens é: " << qtdAvioesRetirados << endl;
        fila->adjustPriority(i);

        if(pista1 > 0)
            pista1--;
        if(pista2 > 0)
            pista2--;
        if(pista3 > 0)
            pista3--;

        cout << endl << "Os aviões que ainda estão em operação são: " << endl;
        fila->writeQueue();
    }

    cout << endl << "Dados Finais: " << endl;
    cout << "Dentre os " << qtdPousos << " pousos realizados, tivemos " << qtdOutroAeroporto << " feitos em outro aeroporto!" << endl;
    cout << "Dentre as " << qtdDecolagens << " decolagens realizadas, tivemos " << totalDecolagensSemAtraso << " feitas sem atraso!"<< endl;

    fila->~PriorityQueue();
}

int decideEmergencia(int probEmergencia){
    int emergencia; // 0 ou 1
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,100); // gerar um numero aleatorio no intervalo [1, 100]

    if(dist(gen) > probEmergencia)
        emergencia = 0;
    else    
        emergencia = 1;

    return emergencia;
}

int decideMaxCombustivel(int tempoCombustivel){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, tempoCombustivel);    // deve conseguir ficar no mínimo mais duas iterações no ar

    return (dist(gen));
}

int decideMaxDecolagem(int tempoVoo){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, tempoVoo);    // deve conseguir ficar no mínimo duas iterações antes de decolar

    return (1.1 * dist(gen));   // adicionamos a tolerancia de 10% do tempo
}

char decideAcao(int probPouso){
    char acao; // 'p' ou 'd' a depender se é pouso ou decolagem
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,100); // gerar um numero aleatorio no intervalo [1, 100]

    if(dist(gen) <= probPouso)
        acao = 'p';
    else    
        acao = 'd';

    return acao;
}

string geradorIdVoo(){
    char idVoo[3];
    string letras = "abcdefghijklmnopqrstuvwxyz";
    
    for(int i = 0; i < 3; i++){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0,25);

        idVoo[i] = letras[dist(gen)];
    }
    return idVoo;
}

string geradorIdAviao(){
    char idAviao[5];
    string numeros = "0123456789";
    string letras = "abcdefghijklmnopqrstuvwxyz";
    
    for(int i = 0; i < 2; i++){ // gerar as duas primeiras letras
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0,25);
        
        idAviao[i] = letras[dist(gen)];
    }

    for(int i = 2; i < 5; i++){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0,9);
        
        idAviao[i] = numeros[dist(gen)];
    }
    return idAviao;
}