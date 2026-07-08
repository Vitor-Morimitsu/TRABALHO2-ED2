#include "aresta.h"
#include "unity.h"

Aresta a;

void setUp(){
    a = criarAresta("a1", "direita", "esquerda", 10.0, 50.0);
}

void tearDown(){
    liberarAresta(a);
}

void teste_criarAresta(){
    TEST_ASSERT_NOT_NULL(a);
    TEST_ASSERT_EQUAL_STRING("a1", getNomeAresta(a));
    TEST_ASSERT_EQUAL_STRING("direita", getCEP_ladoDireitoAresta(a));
    TEST_ASSERT_EQUAL_STRING("esquerda", getCEP_ladoEsquerdoAresta(a));
    TEST_ASSERT_EQUAL_FLOAT(10.0, getCmpAresta(a));
    TEST_ASSERT_EQUAL_FLOAT(50.0, getVmAresta(a));
}

void teste_criarArestaComHifen(){
    Aresta a2 = criarAresta("Rua_X", "-", "cep1", 200.0, 3.5);
    TEST_ASSERT_NOT_NULL(a2);
    TEST_ASSERT_EQUAL_STRING("-", getCEP_ladoDireitoAresta(a2));
    TEST_ASSERT_EQUAL_STRING("cep1", getCEP_ladoEsquerdoAresta(a2));
    liberarAresta(a2);
}

void teste_getNomeAresta(){
    TEST_ASSERT_EQUAL_STRING("a1", getNomeAresta(a));
}

void teste_getCmpAresta(){
    TEST_ASSERT_EQUAL_FLOAT(10.0, getCmpAresta(a));
}

void teste_getVmAresta(){
    TEST_ASSERT_EQUAL_FLOAT(50.0, getVmAresta(a));
}

void teste_setVmAresta(){
    setVmAresta(a, 75.0);
    TEST_ASSERT_EQUAL_FLOAT(75.0, getVmAresta(a));
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarAresta);
    RUN_TEST(teste_criarArestaComHifen);
    RUN_TEST(teste_getNomeAresta);
    RUN_TEST(teste_getCmpAresta);
    RUN_TEST(teste_getVmAresta);
    RUN_TEST(teste_setVmAresta);
    return UNITY_END();
}