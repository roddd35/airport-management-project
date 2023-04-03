#include "aviao.h"

int Plane::getCombustivel(){
    return this->combustivel;
}

int Plane::getPrioridade(){
    return this->prioridade;
}

int Plane::getTempoEspera(){
    return this->tempoEspera;
}

char Plane::getAcao(){
    return this->acao;
}

string Plane::getIdAviao(){
    return this->idAviao;
}

string Plane::getIdVoo(){
    return this->idAviao;
}

void Plane::setAcao(char a){
    this->acao = a;
}

void Plane::setPrioridade(int novapr){
    this->prioridade = novapr;
}

void Plane::setCombustivel(int c){
    this->combustivel = c;
}

void Plane::gastaCombustivel(){
    this->combustivel -= 1;
}

Plane::Plane(int c, int TE, int E, int p, char a, string idV, string idA){
    this->combustivel = c;
    this->tempoEspera = TE;
    this->Emergencia = E;
    this->prioridade = p;
    this->acao = a;
    this->idVoo = idV;
    this->idAviao = idA;
}

Plane::~Plane(){}