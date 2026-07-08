#include "vertice.h"
#include "unity.h"

Vertice v;

void setUp(){
    v = criarVertice("v1", 0.0, 0.0);
}

void tearDown(){
    liberarVertice(v);
}

void teste_criarVertice(){
    TEST_ASSERT_NOT_NULL(v);
    TEST_ASSERT_EQUAL_STRING("v1", getIDVertice(v));
    TEST_ASSERT_EQUAL_FLOAT(0.0, getXVertice(v));
    TEST_ASSERT_EQUAL_FLOAT(0.0, getYVertice(v));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(teste_criarVertice);
    return UNITY_END();
}