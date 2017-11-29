#include "Node.h"

template <class TipoDoElemento>
Node<TipoDoElemento>::Node(const TipoDoElemento info) {
    this->Info = info;
    this->proximo = NULL;
    this->anterior = NULL;
}

template <class TipoDoElemento>
TipoDoElemento Node<TipoDoElemento>::getInfo() const{
    return this->Info;
}

template <class TipoDoElemento>
void Node<TipoDoElemento>::setInfo(const TipoDoElemento &info){
    this->Info = info;
}

template <class TipoDoElemento>
Node<TipoDoElemento> &Node<TipoDoElemento>::getProximo(){
    return this->proximo;
}

template <class TipoDoElemento>
void Node<TipoDoElemento>::setProximo(Node<TipoDoElemento> &node){
    this->proximo = node;
}

template <class TipoDoElemento>
Node<TipoDoElemento> &Node<TipoDoElemento>::getAnterior(){
    return this->anterior;
}

template <class TipoDoElemento>
void Node<TipoDoElemento>::setAnterior(Node<TipoDoElemento> &node){
    this->anterior = node;
}
