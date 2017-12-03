#include "Pilha.h"

template <class T>
void Pilha<T>::trocar(T &num1, T &num2){
   int num3 = num1;
   num1 = num2;
   num2 = num3;
}

template <class T>
void Pilha<T>::selectionSort(int *vetor, int tamanho){
   int k;
   for( int i = 0; i < tamanho; i++ ){
	  k =i;
	  for( int j = tamanho - 1; j > i; j-- ){
		 if(vetor[j] < vetor[k])
			k = j;
	  }
	  trocar( vetor[i], vetor[k] );
   }
}

template <class T>
void Pilha<T>::ordernarPilha() {
    selectionSort(this->PilhaPtr, this->Topo+1);
}

template <class T>
Pilha<T>::Pilha()
{
    PilhaPtr = NULL;
    Topo = -1;
}
template <class T>
void Pilha<T>::pilhaParaVetor(T novoVetor[], const int tamanho) const{
    for(int i = 0; i < tamanho; i++){
        novoVetor[i] = this->PilhaPtr[i];
    }
}

template <class T>
void Pilha<T>::esvaziaPilha() {

    delete[] PilhaPtr;
    PilhaPtr = NULL;
    Topo = -1;
}

template <class T>
Pilha<T>::~Pilha()
{
    if(PilhaPtr != NULL)
        delete [] PilhaPtr;
}

template <class T>
bool Pilha<T>::ItemRepetido(const T &elemento) const{
    if(!this->EstaVazia()){

        //percorro todos os elementos
        for(int i = 0; i <= this->Topo; i++){
            //se for igual
            if(this->PilhaPtr[i] == elemento)
                return true;
        }
    }

    return false;
}

template <class T>
void Pilha<T>::Insere(const T &elemento)
{
    if(Topo != -1)
    {
        T *PtrAux;
        int i;
        PtrAux = new T[++Topo];
        for(i=0;i<Topo;i++)
            PtrAux[i] = PilhaPtr[i];
        delete [] PilhaPtr;
        PilhaPtr = new T[Topo+1];
        for(i=0;i<Topo;i++)
            PilhaPtr[i] = PtrAux[i];
        PilhaPtr[i] = elemento;
        delete [] PtrAux;
    }
    else
    {
        PilhaPtr = new T[1];
        Topo++;
        PilhaPtr[0] = elemento;
    }
}

template <class T>
bool Pilha<T>::Retira(T &elemento)
{
    if(Topo > 0)
    {
        T *PtrAux;
        int i;
        elemento = PilhaPtr[Topo];
        PtrAux = new T[Topo];
        for(i=0;i<Topo;i++)
            PtrAux[i] = PilhaPtr[i];
        delete [] PilhaPtr;
        PilhaPtr = new T[Topo];
        for(i=0;i<Topo;i++)
            PilhaPtr[i] = PtrAux[i];
        Topo--;
        delete [] PtrAux;
    }
    else
    {
        if(Topo == 0)
        {
            elemento = PilhaPtr[Topo];
            Topo--;
            delete [] PilhaPtr;
            PilhaPtr = NULL;
        }
        else
            return false;
    }
    return true;
}

template <class T>
bool Pilha<T>::EstaVazia() const
{
    return Topo == -1;
}

template <class T>
void Pilha<T>::Inverter()
{
    if(!this->EstaVazia()){
        Pilha<T> aux;
        T elemento;

        while(this->Retira(elemento)){
            aux.Insere(elemento);
        }

        (*this) = aux;
    }

}

template <class T>
int Pilha<T>::getTamanho() const
{
   return this->Topo + 1;
}
