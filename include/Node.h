#ifndef NODE_H
#define NODE_H

#include <iostream>

template <class TipoDoElemento>
class Node {

   public:
        Node(const TipoDoElemento info);

        TipoDoElemento getInfo() const;
        void setInfo(const TipoDoElemento &info);

        Node<TipoDoElemento> &getProximo();
        void setProximo(Node<TipoDoElemento> &node);

        Node<TipoDoElemento> &getAnterior();
        void setAnterior(Node<TipoDoElemento> &node);

    private:
        TipoDoElemento Info;
        Node<TipoDoElemento> *proximo;
        Node<TipoDoElemento> *anterior;

};

#endif // NODE_H
