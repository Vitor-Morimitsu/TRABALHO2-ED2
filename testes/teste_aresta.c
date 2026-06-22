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
    TEST_ASSERT_EQUAL_DOUBLE(10.0, getCmpAresta(a));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getVmAresta(a));

}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarAresta);
    return UNITY_END();
}