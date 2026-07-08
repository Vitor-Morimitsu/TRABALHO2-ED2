#include "grafo.h"
#include "vertice.h"
#include "aresta.h"
#include "unity.h"

Grafo g;

void setUp(){
    g = criarGrafo();
}

void tearDown(){
    liberarGrafo(g);
}

// testa se o grafo foi criado corretamente
void teste_criarGrafo(){
    TEST_ASSERT_NOT_NULL(g);
}

// testa inserção de vértice e busca por ID
void teste_inserirEBuscarVertice(){
    Vertice v1 = criarVertice("v1", 10.0, 20.0);
    Vertice v2 = criarVertice("v2", 30.0, 40.0);

    int idx1 = inserirVerticeGrafo(g, v1);
    int idx2 = inserirVerticeGrafo(g, v2);

    // índices devem ser 0 e 1
    TEST_ASSERT_EQUAL_INT(0, idx1);
    TEST_ASSERT_EQUAL_INT(1, idx2);

    // busca por ID deve retornar o índice correto
    TEST_ASSERT_EQUAL_INT(0, buscarVerticeIDGrafo(g, "v1"));
    TEST_ASSERT_EQUAL_INT(1, buscarVerticeIDGrafo(g, "v2"));
}

// testa busca de vértice inexistente
void teste_buscarVerticeInexistente(){
    TEST_ASSERT_EQUAL_INT(-1, buscarVerticeIDGrafo(g, "v99"));
}

// testa inserção de aresta
void teste_inserirAresta(){
    Vertice v1 = criarVertice("v1", 10.0, 20.0);
    Vertice v2 = criarVertice("v2", 30.0, 40.0);
    int idx1 = inserirVerticeGrafo(g, v1);
    int idx2 = inserirVerticeGrafo(g, v2);

    Aresta a = criarAresta("Rua_A", "cep1", "cep2", 100.0, 5.0);

    // não deve causar crash nem erro
    inserirArestaGrafo(g, idx1, idx2, a);
}

// testa inserção de aresta com índice inválido
void teste_inserirArestaIndiceInvalido(){
    Aresta a = criarAresta("Rua_A", "cep1", "cep2", 100.0, 5.0);

    // não deve crashar, deve só printar erro
    inserirArestaGrafo(g, -1, 0, a);
    inserirArestaGrafo(g, 0, 99, a);
    liberarAresta(a);
}

// testa se o grafo expande corretamente quando ultrapassa a capacidade inicial
void teste_expansaoGrafo(){
    // capacidade inicial é 10, insere 15 vértices
    for(int i = 0; i < 15; i++){
        char id[16];
        sprintf(id, "v%d", i);
        Vertice v = criarVertice(id, i * 10.0, i * 10.0);
        int idx = inserirVerticeGrafo(g, v);
        TEST_ASSERT_EQUAL_INT(i, idx);
    }
    // todos devem ser encontrados
    for(int i = 0; i < 15; i++){
        char id[16];
        sprintf(id, "v%d", i);
        TEST_ASSERT_EQUAL_INT(i, buscarVerticeIDGrafo(g, id));
    }
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarGrafo);
    RUN_TEST(teste_inserirEBuscarVertice);
    RUN_TEST(teste_buscarVerticeInexistente);
    RUN_TEST(teste_inserirAresta);
    RUN_TEST(teste_inserirArestaIndiceInvalido);
    RUN_TEST(teste_expansaoGrafo);
    return UNITY_END();
}