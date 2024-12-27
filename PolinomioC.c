#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Estrutura para armazenar um termo do polinômio
typedef struct Poli {
    int coef;   // Coeficiente
    int expo;    // Expoente de X
    struct Poli* proximo;  // Ponteiro para o próximo termo
} Poli;

// Função para criar um novo termo (nó) do polinômio
Poli* criarPoli(int coef, int expo) {
    Poli* novo = (Poli*)malloc(sizeof(Poli));
    novo->coef = coef;
    novo->expo = expo;
    novo->proximo = NULL;
    return novo;
}

// Função para adicionar um termo no polinômio de forma ordenada (maior para menor expoente)
void adicionarTermo(Poli** polinomio, int coef, int expo) {
    Poli* novo = criarPoli(coef, expo);

    // Se a lista estiver vazia ou o novo termo for o maior expoente
    if (*polinomio == NULL || (*polinomio)->expo < novo->expo) {
        novo->proximo = *polinomio;
        *polinomio = novo;
        return;
    }

    // Caso contrário, percorre a lista para encontrar a posição correta para o novo termo
    Poli* atual = *polinomio;
    while (atual->proximo != NULL && atual->proximo->expo > novo->expo) {
        atual = atual->proximo;
    }

    // Inserir o novo termo na posição correta
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}


// Função para avaliar um polinômio para um dado coef de X
int avaliarPolinomio(Poli* polinomio, int x) {
    int resultado = 0;
    while (polinomio != NULL) {
        resultado += polinomio->coef * (int)pow(x, polinomio->expo);
        polinomio = polinomio->proximo;
    }
    return resultado;
}

// Função para somar dois polinômios
Poli* somarPolinomios(Poli* polinomio1, Poli* polinomio2) {
    Poli* resultado = NULL;

    while (polinomio1 != NULL && polinomio2 != NULL) {
        if (polinomio1->expo == polinomio2->expo) {
            int soma_coef = polinomio1->coef + polinomio2->coef;
            if (soma_coef != 0) {  // Não adiciona o termo se o coeficiente for zero
                adicionarTermo(&resultado, soma_coef, polinomio1->expo);
            }
            polinomio1 = polinomio1->proximo;
            polinomio2 = polinomio2->proximo;
        }
        else if (polinomio1->expo > polinomio2->expo) {
            adicionarTermo(&resultado, polinomio1->coef, polinomio1->expo);
            polinomio1 = polinomio1->proximo;
        }
        else {
            adicionarTermo(&resultado, polinomio2->coef, polinomio2->expo);
            polinomio2 = polinomio2->proximo;
        }
    }

    // Adiciona os termos restantes do polinomio1
    while (polinomio1 != NULL) {
        if (polinomio1->coef != 0) {  // Só adiciona se o coeficiente não for zero
            adicionarTermo(&resultado, polinomio1->coef, polinomio1->expo);
        }
        polinomio1 = polinomio1->proximo;
    }

    // Adiciona os termos restantes do polinomio2
    while (polinomio2 != NULL) {
        if (polinomio2->coef != 0) {  // Só adiciona se o coeficiente não for zero
            adicionarTermo(&resultado, polinomio2->coef, polinomio2->expo);
        }
        polinomio2 = polinomio2->proximo;
    }

    return resultado;
}


// Função para subtrair dois polinômios
Poli* subtrairPolinomios(Poli* polinomio1, Poli* polinomio2) {
    Poli* resultado = NULL;

    while (polinomio1 != NULL && polinomio2 != NULL) {
        if (polinomio1->expo == polinomio2->expo) {
            int subtracao_coef = polinomio1->coef - polinomio2->coef;
            if (subtracao_coef != 0) {  // Não adiciona o termo se o coeficiente for zero
                adicionarTermo(&resultado, subtracao_coef, polinomio1->expo);
            }
            polinomio1 = polinomio1->proximo;
            polinomio2 = polinomio2->proximo;
        }
        else if (polinomio1->expo > polinomio2->expo) {
            adicionarTermo(&resultado, polinomio1->coef, polinomio1->expo);
            polinomio1 = polinomio1->proximo;
        }
        else {
            adicionarTermo(&resultado, -polinomio2->coef, polinomio2->expo);
            polinomio2 = polinomio2->proximo;
        }
    }

    // Adiciona os termos restantes do polinomio1
    while (polinomio1 != NULL) {
        if (polinomio1->coef != 0) {  // Só adiciona se o coeficiente não for zero
            adicionarTermo(&resultado, polinomio1->coef, polinomio1->expo);
        }
        polinomio1 = polinomio1->proximo;
    }

    // Adiciona os termos restantes do polinomio2
    while (polinomio2 != NULL) {
        if (polinomio2->coef != 0) {  // Só adiciona se o coeficiente não for zero
            adicionarTermo(&resultado, -polinomio2->coef, polinomio2->expo);
        }
        polinomio2 = polinomio2->proximo;
    }

    return resultado;
}


// Função para derivar um polinômio
Poli* derivarPolinomio(Poli* polinomio) {
    Poli* resultado = NULL;

    while (polinomio != NULL) {
        if (polinomio->expo != 0) {
            int novo_coef = polinomio->coef * polinomio->expo;
            int novo_expo = polinomio->expo - 1;
            adicionarTermo(&resultado, novo_coef, novo_expo);
        }
        polinomio = polinomio->proximo;
    }

    return resultado;
}

// Função para imprimir o polinômio
void imprimirPolinomio(Poli* polinomio) {
    if (polinomio == NULL) {
        printf("Polinômio vazio.\n");
        return;
    }

    // Para verificar se o primeiro termo deve ter um sinal de "+" ou "-"
    int primeiro = 1;

    while (polinomio != NULL) {
        // Condição para não imprimir o sinal "+" para o primeiro termo
        if (primeiro) {
            primeiro = 0;
        }
        else {
            // Se o coef for positivo, coloca o sinal "+"
            if (polinomio->coef > 0) {
                printf(" + ");
            }
            else {
                // Se o coef for negativo, o sinal já é impresso com o número
                printf(" ");
            }
        }

        // Imprimir o coeficiente
        if (polinomio->expo == 0) {
            // Caso o expoente seja 0, não imprime o X
            printf("%d", polinomio->coef);
        }
        else if (polinomio->expo == 1) {
            // Caso o expoente seja 1, imprime só o X (sem o ^1)
            printf("%dx", polinomio->coef);
        }
        else {
            // Para expoentes maiores que 1 ou negativos, imprime o X com o expoente
            printf("%dx^%d", polinomio->coef, polinomio->expo);
        }

        polinomio = polinomio->proximo;
    }
    printf("\n");
}

void liberarPolinomio(Poli* polinomio) {
    Poli* temp;
    while (polinomio != NULL) {
        temp = polinomio;
        polinomio = polinomio->proximo;
        free(temp);
    }
}


int main() {
    Poli* polinomio1 = NULL;
    Poli* polinomio2 = NULL;

    // Criando polinômios 3x^3 + 5x^2 + 2x + 1 e 5x^2 + 4x + 3
    adicionarTermo(&polinomio1, 3, 3);
    adicionarTermo(&polinomio1, 5, 2);
    adicionarTermo(&polinomio1, 2, 1);
    adicionarTermo(&polinomio1, 1, 0);

    adicionarTermo(&polinomio2, 5, 2);
    adicionarTermo(&polinomio2, 4, 1);
    adicionarTermo(&polinomio2, 3, 0);

    printf("Polinomio 1: ");
    imprimirPolinomio(polinomio1);

    printf("Polinomio 2: ");
    imprimirPolinomio(polinomio2);

    // Avaliar o polinômio 1 em x = 2
    printf("Avaliacao do Polinomio 1 em x = 2: %d\n", avaliarPolinomio(polinomio1, 2));

    // Avaliar o polinômio 2 em x = 2
    printf("Avaliacao do Polinomio 2 em x = 2: %d\n", avaliarPolinomio(polinomio2, 2));


    // Somar os polinômios
    Poli* soma = somarPolinomios(polinomio1, polinomio2);
    printf("Soma dos Polinomios: ");
    imprimirPolinomio(soma);
    liberarPolinomio(soma);

    // Subtrair os polinômios
    Poli* subtracao = subtrairPolinomios(polinomio1, polinomio2);
    printf("Subtracao dos Polinomios: ");
    imprimirPolinomio(subtracao);
    liberarPolinomio(subtracao);

    // Derivar o polinômio 1
    Poli* derivada = derivarPolinomio(polinomio1);
    printf("Derivada do Polinomio 1: ");
    imprimirPolinomio(derivada);

    liberarPolinomio(derivada);

    derivada = derivarPolinomio(polinomio2);
    printf("Derivada do Polinomio 2: ");
    imprimirPolinomio(derivada);
    liberarPolinomio(derivada);

    liberarPolinomio(polinomio1);
    liberarPolinomio(polinomio2);


    return 0;
}
