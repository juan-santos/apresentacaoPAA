#include "Lista.h"

template <class TipoDoElemento>
Lista<TipoDoElemento>::Lista() {
    this->primeiro = NULL;
    this->atual = NULL;
    this->ultimo = NULL;

    this->tamanho = 0;
}

template <class TipoDoElemento>
void Lista<TipoDoElemento>::adicionar(const TipoDoElemento &info){

    Node<TipoDoElemento> *node = new Node<TipoDoElemento>(info);

    //se for o primeiro elemento
    if(this->primeiro == NULL){

        this->primeiro = node;
        this->ultimo = node;
        this->atual = node;
    } else {

        node->setAnterior(this->atual);

        //se não for o ultimo elemento
        if(this->atual != this->ultimo){
            node->setProximo(this->atual->getProximo());
            this->atual->getProximo()->setAnterior(node);
        }else{
            //se for o ultimo elemento
            this->ultimo->setProximo(node);
            node->setAnterior(this->ultimo);

            this->ultimo = node;
        }

        this->atual->setProximo(node);
        this->atual = node;
    }

    this->tamanho++;
}

template <class TipoDoElemento>
void Lista<TipoDoElemento>::adicionarUltimo(const TipoDoElemento &info){
    Node<TipoDoElemento> *node = new Node<TipoDoElemento>(info);

    //se for o primeiro elemento
    if(this->primeiro == NULL){

        this->primeiro = node;
        this->ultimo = node;
        this->atual = node;
    } else {

        //se for o ultimo elemento
        this->ultimo->setProximo(node);
        node->setAnterior(this->ultimo);

        this->ultimo = node;
    }

    this->tamanho++;
}

template <class TipoDoElemento>
bool Lista<TipoDoElemento>::removerAtual(){

    if(this->tamanho == 0){
        return false;
    }

    //se for o primeiro elemento
    if(this->atual == this->primeiro){

        //se tiver um unico elemento
        if(this->primeiro == this->ultimo){
            delete atual;
            primeiro = NULL;
            ultimo = NULL;
        }else{
            Node<TipoDoElemento> aux = this->primeiro;

            this->primeiro = atual;
            this->primeiro->setAnterior(NULL);
            delete aux;
        }

    } else{
        //se for o ultimo elemento
        if(this->atual == ultimo){
            this->ultimo->getAnterior()->setProximo(NULL);
            delete ultimo;
        }else{

            Node<TipoDoElemento> aux = this->atual;

            this->atual->getAnterior()->setProximo(this->atual->getProximo());
            this->atual->getProximo()->setAnterior(this->atual->getAnterior());

            this->atual = this->atual->getAnterior();

            delete aux;
        }
    }
}

template <class TipoDoElemento>
int Lista<TipoDoElemento>::getTamanho()const{
    return this->tamanho;
}

template <class TipoDoElemento>
bool Lista<TipoDoElemento>::getProximo(Node<TipoDoElemento> &node){

    if(this->atual == this->ultimo){

        return false;
    } else{

        this->atual = this->atual->getProximo();
        node = atual;
        return true;
    }
}

template <class TipoDoElemento>
bool Lista<TipoDoElemento>::posicionarNoPrimeiro(){
    this->atual = primeiro;
}
