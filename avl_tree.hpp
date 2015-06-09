// Copyright [2015] <Ion>

#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>

template <typename T>
class NoAVL {
 private:
    T* dado;
    int altura;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    explicit NoAVL(const T& dado) : dado(new T(dado)) {
        altura = 0;
        esquerda = NULL;
        direita = NULL;
    }

    virtual ~NoAVL() {
        if (esquerda != NULL)
		    esquerda->~NoAVL();
	    if (direita != NULL)
		    direita->~NoAVL();
	    delete dado;
    }

    int getAltura() {
        return altura;
    }

    int getAltura(NoAVL<T>* nodo) {
        if (nodo == NULL)
            return -1;
        else
            return nodo->getAltura();
    }

    void updateAltura(NoAVL<T> *arv) {
        int maiorAltura;
        if (getAltura(arv->esquerda) > getAltura(arv->direita)) {
            // Maior é o esquerdo
            maiorAltura = getAltura(arv->esquerda);
        } else {
            maiorAltura = getAltura(arv->direita);
        }
        arv->altura = maiorAltura + 1;
    }

    std::vector<NoAVL<T>* > getElementos() {
        return elementos;
    }

    NoAVL<T>* getEsquerda() {
        return esquerda;
    }

    NoAVL<T>* getDireita() {
        return direita;
    }

    NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
	    NoAVL<T> *aux;
	    if (dado < *arv->getDado()) {
	        if (arv->esquerda == NULL) {
	            aux = new NoAVL<T>(dado);
	            if (aux == NULL) {
	                throw "BAD ALLOC";
                }
                arv->esquerda = aux;
            } else {
                aux = arv->inserir(dado, arv->esquerda);
                arv = equilibra(arv, dado);
			    if (arv->getDado() != aux->getDado()) {
			        arv->esquerda = aux;
		        }
            }
        } else {  // direita
	        if (arv->direita == NULL) {
	            aux = new NoAVL<T>(dado);
	            if (aux == NULL) {
	                throw "BAD ALLOC";
	                }
                arv->direita = aux;
            } else {
                aux = arv->inserir(dado, arv->direita);
                arv = equilibra(arv, dado);
			    if (arv->getDado() != aux->getDado()) {
			        arv->direita = aux;
		        }
            }
        }
    	updateAltura(arv);
        return arv;
	}

    NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
        NoAVL<T> *temp, *filho;
        if (arv == NULL) {
            return arv;
        } else if (dado < *arv->getDado()) {
            arv->esquerda = remover(arv->getEsquerda(), dado);
            arv = equilibra(arv, *(maximo(arv))->getDado());
			updateAltura(arv);
            return arv;
        } else if (dado > *arv->getDado()) {
            arv->direita = (remover(arv->getDireita(), dado));
            arv = equilibra(arv, *(minimo(arv))->getDado());
	    	updateAltura(arv);
            return arv;
        } else {
            if (arv->getDireita() != NULL && arv->getEsquerda() != NULL) {
                temp = minimo(arv->getDireita());
                arv->dado = (temp->getDado());
                arv->direita = (remover(arv->getDireita(), *arv->getDado()));
                arv = equilibra(arv, *(minimo(arv))->getDado());
			    updateAltura(arv);
                return arv;
            } else {
                temp = arv;
                if (arv->getDireita() != NULL) {
                    filho = arv->getDireita();
                    return filho;
                } else {
                    if (arv->getEsquerda() != NULL) {
                        filho = arv->getEsquerda();
                        return filho;
                    } else {
                        delete arv;
                        return NULL;
                    }
                }
            }
        }
    }

    NoAVL<T> *rodaEsquerda(NoAVL<T> *arv) {
		NoAVL<T> *aux = arv->esquerda;
	    arv->esquerda = aux->direita;
	    aux->direita = arv;
		updateAltura(arv);
		updateAltura(aux);
		return aux;
    }

    NoAVL<T> *rodaDireita(NoAVL<T> *arv) {
		NoAVL<T> *aux = arv->direita;
		arv->direita = aux->esquerda;
		aux->esquerda = arv;
		updateAltura(arv);
		updateAltura(aux);
	    return aux;
	}

    NoAVL<T>* rodaEsquerdaDuplo(NoAVL<T> *arv) {
        arv->esquerda = rodaDireita(arv->esquerda);
        return rodaEsquerda(arv);
    }

    NoAVL<T>* rodaDireitaDuplo(NoAVL<T> *arv) {
        arv->direita = rodaEsquerda(arv->direita);
        return rodaDireita(arv);
    }

    NoAVL<T>* equilibra(NoAVL<T> *arv, const T& dado) {
        int alturaEsquerda = getAltura(arv->getEsquerda());
        int alturaDireita = getAltura(arv->getDireita());
        if (dado < *arv->getDado()) {
            if (alturaEsquerda - alturaDireita == 2) {
	            if (dado < *(arv->getEsquerda())->getDado()) {
		            return rodaEsquerda(arv);
	            } else {
		            return rodaEsquerdaDuplo(arv);
	            }
            }
        } else {
            if (alturaDireita - alturaEsquerda == 2) {
	            if (dado > *(arv->getDireita())->getDado()) {
    		        return rodaDireita(arv);
    	        } else {
	        	    return rodaDireitaDuplo(arv);
	            }
            }
        }
        return arv;
    }

    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        if (nodo->getEsquerda() != NULL)
            return minimo(nodo->getEsquerda());
        else
            return nodo;
    }

    NoAVL<T>* maximo(NoAVL<T>* nodo) {
        if (nodo->getDireita() != NULL)
            return maximo(nodo->getDireita());
        else
            return nodo;
    }

    T* getDado() {
        return dado;
    }

    T* busca(const T& dado, NoAVL<T>* arv) {
                while (arv != NULL) {
            if (*arv->getDado() != dado) {
                if (*arv->getDado() < dado)
                    arv = arv->getDireita();
                else
                    arv = arv->getEsquerda();
            } else {
                return arv->getDado();
            }
        }
        throw "Elemento não encotnrado";
    }

    void preOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }

    void emOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }

    void posOrdem(NoAVL<T>* nodo) {
        if (nodo != NULL) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
};

#endif /* NO_AVL_HPP */

