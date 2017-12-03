#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include <iostream>

using namespace std;

template <class T>
class Pilha {

    public:
        Pilha();
        ~Pilha();
        void Insere(const T &elemento);
        bool Retira(T &elemento);
        bool EstaVazia() const;
        void Inverter();
        int getTamanho() const;
        bool ItemRepetido(const T &elemento) const;
        void pilhaParaVetor(T elemento[], const int) const;
        void esvaziaPilha();
        void ordernarPilha();
    private:
        T *PilhaPtr;
        int Topo;

        void trocar(T &num1, T &num2);
        void selectionSort(int *vetor, int tamanho);
};

#endif // PILHA_H_INCLUDED
