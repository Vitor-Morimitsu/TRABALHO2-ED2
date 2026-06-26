#include "arvore.h"
#include "quadra.h"
#include "unity.h"

Arvore a;

void setUp(){
    a = criarArvore();
}

void tearDown(){
    liberarArvore(a);
}

void teste_criarArvore(){
    TEST_ASSERT_NOT_NULL(a);
}

void teste_buscarArvoreVazia(){
    // buscar em árvore vazia deve retornar NULL sem crashar
    TEST_ASSERT_NULL(buscarArvore("cep1", a));
}

void teste_inserirEBuscar(){
    Quadra q = criarQuadra();
    setCEPQuadra(q, "cep1");
    setDimensoesQuadra(q, 0.0, 0.0, 100.0, 60.0);

    inserirArvore(q, a);

    Quadra encontrada = buscarArvore("cep1", a);
    TEST_ASSERT_NOT_NULL(encontrada);
    TEST_ASSERT_EQUAL_STRING("cep1", getCEPQuadra(encontrada));
}

void teste_buscarInexistente(){
    Quadra q = criarQuadra();
    setCEPQuadra(q, "cep1");
    inserirArvore(q, a);

    // busca por CEP que não existe
    TEST_ASSERT_NULL(buscarArvore("cep99", a));
}

void teste_inserirVarios(){
    // insere fora de ordem alfabética para testar os dois lados da BST
    char* ceps[] = {"cep5", "cep2", "cep8", "cep1", "cep3"};
    for(int i = 0; i < 5; i++){
        Quadra q = criarQuadra();
        setCEPQuadra(q, ceps[i]);
        inserirArvore(q, a);
    }

    // todos devem ser encontrados
    for(int i = 0; i < 5; i++){
        Quadra encontrada = buscarArvore(ceps[i], a);
        TEST_ASSERT_NOT_NULL(encontrada);
        TEST_ASSERT_EQUAL_STRING(ceps[i], getCEPQuadra(encontrada));
    }
}

void teste_inserirDuplicado(){
    Quadra q1 = criarQuadra();
    setCEPQuadra(q1, "cep1");
    inserirArvore(q1, a);

    Quadra q2 = criarQuadra();
    setCEPQuadra(q2, "cep1");
    inserirArvore(q2, a);  // duplicado deve ser ignorado

    // deve encontrar normalmente, sem crash
    Quadra encontrada = buscarArvore("cep1", a);
    TEST_ASSERT_NOT_NULL(encontrada);
    TEST_ASSERT_EQUAL_STRING("cep1", getCEPQuadra(encontrada));

    // libera o duplicado manualmente pois não foi inserido na árvore
    liberarQuadra(q2);
}

void teste_ordemBST(){
    // insere em ordem que força o uso dos dois lados
    Quadra qRaiz = criarQuadra();
    setCEPQuadra(qRaiz, "cep5");
    inserirArvore(qRaiz, a);

    Quadra qEsq = criarQuadra();
    setCEPQuadra(qEsq, "cep2");  // vai para esquerda de cep5
    inserirArvore(qEsq, a);

    Quadra qDir = criarQuadra();
    setCEPQuadra(qDir, "cep8");  // vai para direita de cep5
    inserirArvore(qDir, a);

    TEST_ASSERT_NOT_NULL(buscarArvore("cep5", a));
    TEST_ASSERT_NOT_NULL(buscarArvore("cep2", a));
    TEST_ASSERT_NOT_NULL(buscarArvore("cep8", a));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarArvore);
    RUN_TEST(teste_buscarArvoreVazia);
    RUN_TEST(teste_inserirEBuscar);
    RUN_TEST(teste_buscarInexistente);
    RUN_TEST(teste_inserirVarios);
    RUN_TEST(teste_inserirDuplicado);
    RUN_TEST(teste_ordemBST);
    return UNITY_END();
}