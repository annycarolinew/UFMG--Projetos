#include <sstream>
#include <iostream>
#include "groups.hpp"

Pacote::Pacote(int id, int arm_o, int arm_d, Cliente* remet, Cliente* dest){
    this->id_pct = id;
    this->arm_origem = arm_o;
    this->arm_destino = arm_d;
    this->remetente = remet;
    this->destinatario = dest;
}

int Pacote::GetID(){
    return this->id_pct;
}

const List<Evento*>& Pacote::GetEvento(int i){
    return this->eventos[i];
}

Evento* Pacote::GetEventoInicio(){
    const No<Evento*>* no = this->eventos[0].GetFoot();
    return no->data;
}

Evento* Pacote::GetEventoFim(){
    const No<Evento*>* no = this->eventos[1].GetFoot();
    return no->data;
}

void Pacote::SetEvento(Evento* e){
    if(this->eventos[0].GetHead() == nullptr && this->eventos[1].GetHead() == nullptr){
        this->eventos[0].Insere(e);

    }else if(this->eventos[1].GetFoot() != nullptr){

        if(this->eventos[1].GetFoot()->data->tempo < e->tempo){
            this->eventos[1].reset();
            this->eventos[1].Insere(e);
        }else if(this->eventos[1].GetFoot()->data->tempo == e->tempo){
            this->eventos[1].Insere(e);
        }

    }else if(this->eventos[1].GetFoot() == nullptr){
        this->eventos[1].Insere(e);
    }
}


Pacote::~Pacote(){
    
}


Cliente::Cliente(std::string nome){
    this->nome = nome;
}

void Cliente::SetPacote(Pacote* pct){
    this->pacotes.Insere(pct);
}

std::ostream& operator<<(std::ostream& os, const PacoteTempo& pt) {
    os << "ID: " << pt.id << " | Tempo: " << pt.tempo;

    if (pt.e != nullptr) {
        os << " | Evento: " << pt.e->print();
    } else {
        os << " | Evento: [null]";
    }

    return os;
}

void Cliente::GetPacotes(List<PacoteTempo*>& eventos){
    AVL<int, PacoteTempo*> avl_eventos;
    No<Pacote*>* aux_pct = this->pacotes.GetHead();

    while (aux_pct != nullptr) {
        const List<Evento*>& ini_eventos = aux_pct->data->GetEvento(0); 
        const List<Evento*>& fim_eventos = aux_pct->data->GetEvento(1); 

        const No<Evento*>* aux_hd = ini_eventos.GetHead();
        while(aux_hd != nullptr) {
            PacoteTempo* pct = new PacoteTempo(aux_hd->data->tempo, aux_hd->data->id_pct, aux_hd->data);
            avl_eventos.Insere(pct->tempo, pct);
            aux_hd = aux_hd->prox;
        }

        const No<Evento*>* aux_ft = fim_eventos.GetHead();
        while(aux_ft != nullptr){
            PacoteTempo* pct = new PacoteTempo(aux_ft->data->tempo, aux_ft->data->id_pct, aux_ft->data);
            avl_eventos.Insere(pct->tempo, pct);        
            aux_ft = aux_ft->prox; 
        }

        aux_pct = aux_pct->prox;      
        
    }
 
    avl_eventos.getInOrder(eventos);
}

std::string Cliente::GetNome(){
    return this->nome;
}

Cliente::~Cliente(){
    this->pacotes.deleteList();
}
