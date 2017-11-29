#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "Node.h"

template <class TipoDoElemento>
class Lista {

    public:
        Lista();

        void adicionar(const TipoDoElemento &info);
        void adicionarUltimo(const TipoDoElemento &info);

        bool removerAtual();

        int getTamanho() const;

        bool getProximo(Node<TipoDoElemento> &node);

        bool posicionarNoPrimeiro();

    private:
        Node<TipoDoElemento> *primeiro;
        Node<TipoDoElemento> *atual;
        Node<TipoDoElemento> *ultimo;
        int tamanho;
};

#endif // LISTA_H
