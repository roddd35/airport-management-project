#include "filaPrioridades.h"

int PriorityQueue::isEmpty(){
    return this->n;
}

void PriorityQueue::resizePriorityQueue(){
    Item *novo = (Item*)malloc(2 * this->max * sizeof(Item));
    for(int i = 0; i < this->n; i++)
        novo[i] = this->v[i];
    free(this->v);
    this->v = novo;
    this->max = 2 * this->max;
}

int PriorityQueue::removePriorityQueue(){
    int aux;
    if(!isEmpty()){
        aux = this->v[0].elemento;
        this->indice[aux] = -1;
        this->v[0] = this->v[this->n - 1];
        this->indice[this->v[0].elemento] = 0;
        this->n = this->n - 1;
        // rebaixa(f, 0); colocar qnd fazer o heap
        return aux;
    }
}

void PriorityQueue::insertPriorityQueue(Item x){
    if(this->n == this->max)
        // PriorityQueue.resizeFilaPrior(); VER COMO FAZER ISSO DAQUI
        // PROVAVELMENTE TEREMOS QUE PASSAR A FILA QUE ESTAMOS USANDO PRA FUNÇÃO
    this->v[this->n] = x;
    this->indice[x.elemento] = this->n;
    this->n += 1;

    sobe(this->n - 1);
}

int PriorityQueue::getElemento(int posicao){
    return this->v[posicao].elemento;
}

void PriorityQueue::changePriority(int indice, int novapr){
    int auxPrior = this->v[indice].prioridade;

    this->v[indice].prioridade = novapr;
    if(auxPrior < novapr)
        sobe(indice);
    else
        rebaixa(indice);
}

void PriorityQueue::sobe(int i){
    int pai, filho;
    Item aux;
    filho = i;
    pai = (i - 1) / 2;

    if(filho > 1 && this->v[filho].prioridade > this->v[pai].prioridade){
        aux = this->v[pai];
        this->v[pai] = this->v[filho];
        this->v[filho] = aux;

        this->indice[this->v[pai].elemento] = pai;
        this->indice[this->v[filho].elemento] = filho;
        sobe(pai);
    }
}

void PriorityQueue::rebaixa(int i){
    int maior, pai, filhoEsq, filhoDir;
    Item aux;

    pai = i;
    filhoEsq = 2 * i + 1;
    filhoDir = 2 * i + 2;

    maior = i;
    if(filhoEsq < this->n && this->v[filhoEsq].prioridade > this->v[maior].prioridade)
        maior = filhoEsq;
    
    if(filhoDir < this->n && this->v[filhoDir].prioridade > this->v[maior].prioridade)
        maior = filhoDir;

    if(maior != pai){
        aux = this->v[maior];
        this->v[maior] = this->v[pai];
        this->v[pai] = aux;

        this->indice[this->v[maior].elemento] = maior;
        this->indice[this->v[pai].elemento] = pai;
        rebaixa(maior);
    }
}

PriorityQueue::PriorityQueue(int max, int tam){
    this->v = (Item*)malloc(max * sizeof(Item));
    this->indice = (int*)malloc(tam * sizeof(int));
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

// REVISAR E ARRUMAR TUDO
int main(){
    Item novo;
    int n;
    int j;
    int valor;

    n = 15;
    PriorityQueue *filaPrioridade = new PriorityQueue(1, n);

    for(int i = 0; i < n; i++){
        novo.elemento = i;
        novo.prioridade = 100-i;
        filaPrioridade->insertPriorityQueue(novo);
    }

    cout << "----------" << endl;

    filaPrioridade->changePriority(6, 1000);
    filaPrioridade->changePriority(8, 900);

    for(int i = 0; i < n; i++){
        valor = filaPrioridade->getElemento(i);
        cout << endl << valor;
    }

    cout << "----------" << endl;

    for(int i = 0; i < n; i++){
        j = filaPrioridade->removePriorityQueue();
        cout << "Removido: " << j;
        for(j = 0; j < n; j++){
            valor = filaPrioridade->getElemento(j);
            cout << endl << valor;
        }
        cout << "**********" << endl;
    }
}
