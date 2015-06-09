// "Copyright [year] <Ion>"
    #ifndef NO_BINARIO_HPP
    #define NO_BINARIO_HPP

    #include <cstdlib>
    #include <vector>

    template <typename T>
    class NoBinario {
     protected:
        T* dado;
        NoBinario<T>* esquerda;
        NoBinario<T>* direita;
        std::vector<NoBinario<T>* > elementos; 
                                              

     public:
        NoBinario<T>(const T& info) {
          esquerda = NULL;
          direita = NULL;
          dado = new T(info);
          elementos.clear();
        }

        virtual ~NoBinario() {}

        T* getDado() {
          return dado;
        }

        std::vector< NoBinario<T>* > getElementos() {
          return elementos;
        }
        NoBinario<T>* getEsquerda() {
          return esquerda;
        }
        NoBinario<T>* getDireita() {
          return direita;
        }
        T* busca(const T& dado, NoBinario<T>* arv) {
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
          throw "ERRO D:";
        }
        NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
          if (dado < *arv->getDado()) {
            if (arv->getEsquerda() == NULL) {
              arv->esquerda = new NoBinario<T>(dado);
              return arv->getEsquerda();
            } else {
              inserir(dado, arv->getEsquerda());
            }
          } else {
            if (arv->getDireita() == NULL) {
                arv->direita = new NoBinario<T>(dado);
                return arv->getDireita();
            } else {
              inserir(dado, arv->getDireita());
            }
          }
          return NULL;
        }

        NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
          NoBinario<T> *aux, *filho;
          if (arv == NULL) {
            return arv;
          } else {
            if (dado < *arv->getDado()) {
              arv->esquerda = remover(arv->getEsquerda(), dado);
              return arv;
            } else {
              if (dado > *arv->getDado()) {
                arv->direita = remover(arv->getDireita(), dado);
                return arv;
              } else {
                if (arv->getDireita() != NULL && arv->getEsquerda() != NULL) {
                  aux = minimo(arv->getDireita());
                  arv->dado = aux->getDado();
                  arv->direita = remover(arv->getDireita(), *arv->getDado());
                  return arv;
                } else {
                  aux = arv;
                  if (arv->getDireita() != NULL) {
                    filho = arv->getEsquerda();
                    return filho;
                  } else {
                      if (arv->getEsquerda() != NULL) {
                        filho = arv->getEsquerda();
                        return filho;
                      } else {}
                    delete arv;
                    return NULL;
                  }
                }
              }
            }
          }
        }

        NoBinario<T>* minimo(NoBinario<T>* nodo) {
          while (nodo->getEsquerda() != NULL) {
            nodo = nodo->getEsquerda();
          }
          return nodo;
        }
        void preOrdem(NoBinario<T>* nodo) {
          if (nodo != NULL) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
          }
        }
        void emOrdem(NoBinario<T>* nodo) {
           if (nodo != NULL) {
            preOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            preOrdem(nodo->getDireita());
          }
        }
        void posOrdem(NoBinario<T>* nodo){
           if (nodo != NULL) {
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
            elementos.push_back(nodo);
          }
        }
    };

#endif

