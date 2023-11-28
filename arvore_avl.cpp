#include <iostream>

using namespace std;

class No {
private:
    int valor;
    No *esquerda;
    No *direita;
    int altura;

public:
    No() {
        this->valor = 0;
        this->esquerda = nullptr;
        this->direita = nullptr;
        this->altura = 0;
    }

    No(int valor) : No() {
        this->valor = valor;
    }

    void set_valor(int valor) { this->valor = valor; }
    void set_esquerda(No *esquerda) { this->esquerda = esquerda; }
    void set_direita(No *direita) { this->direita = direita; }
    void set_altura(int altura) { this->altura = altura; }

    int get_valor() { return this->valor; }
    No *get_esquerda() { return this->esquerda; }
    No *get_direita() { return this->direita; }
    int get_altura() { return this->altura; }

    bool eh_folha() { return this->esquerda == nullptr && this->direita == nullptr; }
    int grau() { return (this->esquerda != nullptr) + (this->direita != nullptr); }
};

class Arvore {
private:
    No *raiz;

public:
    Arvore() { this->raiz = nullptr; }

    No *get_raiz() { return this->raiz; }

    void set_raiz(No *raiz) { this->raiz = raiz; }

    No *inserir(No *raiz, int valor) {
        if(raiz == nullptr)
            return new No(valor);
        else if(valor < raiz->get_valor())
            raiz->set_esquerda(inserir(raiz->get_esquerda(), valor));
        else if(valor > raiz->get_valor())
            raiz->set_direita(inserir(raiz->get_direita(), valor));

        raiz->set_altura(maior(altura_no(raiz->get_esquerda()), altura_no(raiz->get_direita())) + 1);
        return balancear(raiz);
    }

    No *balancear(No *raiz) {
        int fb = fator_de_balanceamento(raiz);

        if(fb == 2) {
            if(fator_de_balanceamento(raiz->get_esquerda()) >= 0)
                raiz = rotacao_direita(raiz);
            else
                raiz = rotacao_esquerda_direita(raiz);
        }
        else if(fb == -2) {
            if(fator_de_balanceamento(raiz->get_direita()) <= 0)
                raiz = rotacao_esquerda(raiz);
            else
                raiz = rotacao_direita_esquerda(raiz);
        }

        return raiz;
    }

    int fator_de_balanceamento(No *raiz) {
        if(raiz == nullptr)
            return 0;
        return altura_no(raiz->get_esquerda()) - altura_no(raiz->get_direita());
    }

    No *rotacao_esquerda(No *r) {
        No *y = r->get_direita();
        No *f = y->get_esquerda();

        y->set_esquerda(r);
        r->set_direita(f);

        r->set_altura(maior(altura_no(r->get_esquerda()), altura_no(r->get_direita())) + 1);
        y->set_altura(maior(altura_no(y->get_esquerda()), altura_no(y->get_direita())) + 1);

        return y;
    }

    No *rotacao_direita(No *r) {
        No *y = r->get_esquerda();
        No *f = y->get_direita();

        y->set_direita(r);
        r->set_esquerda(f);

        r->set_altura(maior(altura_no(r->get_esquerda()), altura_no(r->get_direita())) + 1);
        y->set_altura(maior(altura_no(y->get_esquerda()), altura_no(y->get_direita())) + 1);

        return y;
    }

    No *rotacao_esquerda_direita(No *r) {
        r->set_esquerda(rotacao_esquerda(r->get_esquerda()));
        return rotacao_direita(r);
    }

    No *rotacao_direita_esquerda(No *r) {
        r->set_direita(rotacao_direita(r->get_direita()));
        return rotacao_esquerda(r);
    }

    int maior(int a, int b) {
        return (a > b) ? a : b;
    }

    int altura_no(No *raiz) {
        if(raiz == nullptr)
            return -1;
        return raiz->get_altura();
    }

    No *minimo(No *raiz) {
        if(raiz->get_esquerda() != nullptr)
            return minimo(raiz->get_esquerda());
        else
            return raiz;
    }

    No *remover(No *raiz, int valor) {
        if(raiz == nullptr)
            return nullptr;
        if(valor < raiz->get_valor()) {
            raiz->set_esquerda(remover(raiz->get_esquerda(), valor));
        }
        else if(valor > raiz->get_valor()) {
            raiz->set_direita(remover(raiz->get_direita(), valor));
        }
        else {
            if (raiz->get_direita() == nullptr || raiz->get_esquerda() == nullptr) {
                No *aux = (raiz->get_direita() == nullptr) ? raiz->get_esquerda() : raiz->get_direita();
                delete raiz;
                return aux;
            }
            else {
                No *sucessor = minimo(raiz->get_direita());
                raiz->set_valor(sucessor->get_valor());
                raiz->set_direita(remover(raiz->get_direita(), sucessor->get_valor()));
            }
        }

        raiz->set_altura(maior(altura_no(raiz->get_esquerda()), altura_no(raiz->get_direita()))+1);
        return balancear(raiz);
    }

    void imprimir(No *raiz, int nivel) {
        if(raiz != nullptr) {
            imprimir(raiz->get_direita(), nivel+1);
            printf("\n\n");

            for(int i = 0; i < nivel; i++)
                printf("\t");
            
            printf("%d", raiz->get_valor());
            imprimir(raiz->get_esquerda(), nivel+1);
        }
    }
};

int main(void) {

    Arvore arvore;

    int opcao, valor;

    do {
        printf("\n\n0 - Sair\n1 - Inserir\n2 - Remover\n3 - Imprimir\n\n");
        cin >> opcao;

        switch (opcao) {
        case 1:
            printf("\nDigite o valor a ser inserido: ");
            cin >> valor;
            arvore.set_raiz(arvore.inserir(arvore.get_raiz(), valor));
            break;
        case 2:
            printf("\nDigite o valor a ser removido: ");
            cin >> valor;
            arvore.set_raiz(arvore.remover(arvore.get_raiz(), valor));
            break;
        case 3:
            arvore.imprimir(arvore.get_raiz(), 1);
            break;
        default:
            break;
        }
    } while(opcao != 0);

    return 0;
}