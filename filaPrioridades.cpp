#include "filaPrioridades.h"

PriorityQueue::PriorityQueue(int max, int tam){
    this->v = (Plane*)malloc(sizeof(Plane) * max);
    this->indice = (int*)malloc(sizeof(int) * tam);

    for(int i = 0; i < tam; i++)
        this->indice[i] = -1;

    this->n = 0;
    this->max = max;
    this->tamanho = tam;
}

PriorityQueue::~PriorityQueue(){
    free(this->v);
    free(this->indice);
}

void PriorityQueue::insertPriorityQueue(Plane *x){
    if(this->n == this->max)
        this->resizePriorityQueue();
    this->v[this->n] = *x;
    if(x->getAcao() == 'p')
        this->indice[x->getCombustivel()] = this->n;
    else
        this->indice[x->getTempoEspera()] = this->n;
    this->n += 1;

    sobe(this->n - 1);
}

void PriorityQueue::changePriority(int indice, int novapr){
    int auxPrior = this->v[indice].getPrioridade();

    this->v[indice].setPrioridade(novapr);
    if(auxPrior < novapr)
        sobe(indice);
    else
        rebaixa(indice);
}

void PriorityQueue::resizePriorityQueue(){
    Plane *novo = (Plane*)malloc(2 * this->max * sizeof(Plane));

    for(int i = 0; i < this->n; i++)
        novo[i] = this->v[i];
    free(this->v);
    this->v = novo;
    this->max = 2 * this->max;
}

void PriorityQueue::writeQueue(){
    cout << endl;
    if(this->n != 0){
        for(int i = 0; i < this->n; i++){
            if(this->v[i].getAcao() == 'p')
                cout << "Aviao: " << this->v[i].getIdAviao() << " Origem: " << this->v[i].getIdVoo() << " Combustível: " << this->v[i].getCombustivel() << endl;
            else
                cout << "Aviao: " << this->v[i].getIdAviao() << " Destino: " << this->v[i].getIdVoo() << " Saída: " << this->v[i].getTempoEspera() << "h" << endl;
        }
    }
    cout << endl;
}

void PriorityQueue::adjustPriority(int tempoAtual){
    for(int i = 0; i < this->n; i++){
        if(this->v[i].getCombustivel() == 0 || this->v[i].getTempoEspera() <= tempoAtual)
            this->changePriority(i, 2);

        if(this->v[i].getAcao() == 'p' && this->v[i].getCombustivel() > 0)
            this->v[i].gastaCombustivel();
    }
}

// OBS TALVEZ MUDAR PARA GETPRIORIDADE ONDE ESTA GETCOMBUSTIVEL E GETTEMPOESPERA
void PriorityQueue::sobe(int i){
    int pai, filho;
    Plane aux;

    filho = i;
    pai = (i - 1) / 2;

    if(filho >= 1 && this->v[filho].getPrioridade() > this->v[pai].getPrioridade()){
        aux = this->v[pai];
        this->v[pai] = this->v[filho];
        this->v[filho] = aux;

        aux.~Plane();

        this->indice[this->v[pai].getPrioridade()] = pai;
        this->indice[this->v[filho].getPrioridade()] = filho;

        sobe(pai);
    }
}

void PriorityQueue::rebaixa(int i){
    int maior, pai, filhoEsq, filhoDir;
    Plane aux;

    pai = i;
    filhoEsq = 2 * i + 1;
    filhoDir = 2 * i + 2;

    maior = i;
    if(filhoEsq < this->n && this->v[filhoEsq].getPrioridade() > this->v[maior].getPrioridade())
        maior = filhoEsq;

    if(filhoDir < this->n && this->v[filhoDir].getPrioridade() > this->v[maior].getPrioridade())
        maior = filhoDir;
    if(maior != pai){
        aux = this->v[maior];
        this->v[maior] = this->v[pai];
        this->v[pai] = aux;

        this->indice[this->v[maior].getPrioridade()] = maior;
        this->indice[this->v[pai].getPrioridade()] = pai; 

        rebaixa(maior);
    }
}

int PriorityQueue::isEmpty(){
    return (this->n == 0);
}

int PriorityQueue::removePriorityQueue(string idVoo, string idAviao, int index){
    int aux;
    if(!this->isEmpty()){
        if(this->v[index].getAcao() == 'p'){
            aux = this->v[index].getCombustivel();
            this->indice[this->v[index].getCombustivel()] = 0;
        }
        else{
            aux = this->v[index].getTempoEspera();
            this->indice[this->v[index].getTempoEspera()] = 0;
        }
        this->indice[aux] = -1;
        this->v[index] = this->v[this->n - 1];
        this->n = this->n - 1;

        rebaixa(index);
        return aux;
    }
    return 0;
}

int PriorityQueue::removePlanes(int qtdAvioesRetirados, int *pista1, int *pista2, int *pista3, int tempoAtual, int *qtdOutroAeroporto, int *qtdPousos, int *qtdDecolagens, int *decolagensSemAtraso){
    int contaPrioridade = 0;

    // deve vir antes pois só pode decolar nesse aeroporto
    for(int i = 0; i < this->n; i++){
        if(this->v[i].getAcao() == 'd' && this->v[i].getPrioridade() == 2 && this->v[i].getTempoEspera() == tempoAtual){
            if(*pista3 == 0){
                *pista3 = 3; //desativada por 3 turnos
                cout << "O avião: " << this->v[i].getIdAviao() << " com destino: " << this->v[i].getIdVoo() << " decolou na pista 3, com atraso de: " << this->v[i].getAtraso() << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                *qtdDecolagens += 1;
                if(this->v[i].getAtraso() == 0)
                    *decolagensSemAtraso += 1;
                qtdAvioesRetirados++;
                this->n -= 1;
            }
            else if(*pista1 == 0){
                *pista1 = 3;
                cout << "O avião: " << this->v[i].getIdAviao() << " com destino: " << this->v[i].getIdVoo() << " decolou na pista 1, com atraso de: " << this->v[i].getAtraso() << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdDecolagens += 1;
                if(this->v[i].getAtraso() == 0)
                    *decolagensSemAtraso += 1;
                this->n -= 1;
            }
            else if(*pista2 == 0){
                *pista2 = 3;
                cout << "O avião: " << this->v[i].getIdAviao() << " com destino: " << this->v[i].getIdVoo() << " decolou na pista 3, com atraso de: " << this->v[i].getAtraso() << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdDecolagens += 1;
                if(this->v[i].getAtraso() == 0)
                    *decolagensSemAtraso += 1;
                this->n -= 1;
            }
            else
                this->v[i].aumentaTempoEspera();
        }

        // remover aviões de EMERGÊNCIA ou SEM COMBUSTÍVEL! 
        else if(this->v[i].getPrioridade() == 3 || (this->v[i].getPrioridade() == 2 && this->v[i].getAcao() == 'p' && this->v[i].getCombustivel() == 0)){
            if(*pista1 == 0){
                *pista1 = 3;
                if(this->v[i].getPrioridade() == 2)
                    cout << "O avião: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 1 sem combustível!" << endl;
                else
                    cout << "O avião emergencial: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 1!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                this->n -= 1;
            }
            else if(*pista2 == 0){
                *pista2 = 3;
                if(this->v[i].getPrioridade() == 2)
                    cout << "O avião: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 3 sem combustível!" << endl;
                else
                    cout << "O avião emergencial: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 3!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                this->n -= 1;
            }
            else if(*pista3 == 0 && this->v[i].getPrioridade() == 3){   // apenas aviões de emergência podem pousar na pista 3
                *pista3 = 3;
                cout << "O avião emergencial: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 3!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                this->n -= 1;
            }
            else{
                if(this->v[i].getPrioridade() == 2)
                    cout << "O avião: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " foi enviado para outro aeroporto sem combustível!" << endl;
                else
                    cout << "O avião emergencial: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " foi enviado para outro aeroporto!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                *qtdOutroAeroporto += 1;
                this->n -= 1;
            }
        }
    }
    // retirar o restante dos aviões caso tenha sobrado pistas
    while(*pista1 == 0 || *pista2 == 0){
        for(int i = 0; i < this->n; i++){
            if(*pista1 == 0){
                *pista1 = 3;
                cout << "O avião: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 1!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                this->n -= 1;
            }
            else if(*pista2 == 0){
                *pista2 = 3;
                cout << "O avião: " << this->v[i].getIdAviao() << " de voo: " << this->v[i].getIdVoo() << " pousou na pista 3!" << endl;
                this->removePriorityQueue(this->v[i].getIdAviao(), this->v[i].getIdVoo(), i);
                qtdAvioesRetirados++;
                *qtdPousos += 1;
                this->n -= 1;
            }
        }
    }
    return qtdAvioesRetirados;
}