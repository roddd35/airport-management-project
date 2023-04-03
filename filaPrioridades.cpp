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

int PriorityQueue::isEmpty(){
    return (this->n == 0);
}

int PriorityQueue::removePriorityQueue(){

    int aux;
    if(!this->isEmpty()){
        if(this->v[0].getAcao() == 'p'){
            aux = this->v[0].getCombustivel();
            this->indice[this->v[0].getCombustivel()] = 0;
        }
        else{
            aux = this->v[0].getTempoEspera();
            this->indice[this->v[0].getTempoEspera()] = 0;
        }
        this->indice[aux] = -1;
        this->v[0] = this->v[this->n - 1];
        this->n = this->n - 1;

        rebaixa(0);
        return aux;
    }
    return 0;
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
    for(int i = 0; i < this->n; i++)
        cout << "Aviao: " << this->v[i].getIdAviao() << " Prioridade: " << this->v[i].getPrioridade() << endl;
}

void PriorityQueue::sobe(int i){
    int pai, filho;
    Plane aux;

    filho = i;
    pai = (i - 1) / 2;

    if(filho >= 1 && this->v[filho].getPrioridade() > this->v[pai].getPrioridade()){
        aux = this->v[pai];
        this->v[pai] = this->v[filho];
        this->v[filho] = aux;

        if(this->v->getAcao() == 'p'){
            this->indice[this->v[pai].getCombustivel()] = pai;
            this->indice[this->v[filho].getCombustivel()] = filho;
        }
        else{
            this->indice[this->v[pai].getTempoEspera()] = pai;
            this->indice[this->v[filho].getTempoEspera()] = filho;
        }
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

        if(this->v->getAcao() == 'p'){
            this->indice[this->v[maior].getCombustivel()] = maior;
            this->indice[this->v[pai].getCombustivel()] = pai; 
        }
        else{
            this->indice[this->v[maior].getTempoEspera()] = maior;
            this->indice[this->v[pai].getTempoEspera()] = pai; 
        }
        rebaixa(maior);
    }
}