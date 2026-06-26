#include "registrador.h"
#include "unity.h"

Registrador r;

void setUp(){
    r = criarRegistrador("cep1", 'S', 45);
}

void tearDown(){
    liberarRegistrador(r);
}

void teste_criarRegistrador(){
    TEST_ASSERT_NOT_NULL(r);
    TEST_ASSERT_EQUAL_STRING("cep1", getCepRegistrador(r));
    TEST_ASSERT_EQUAL_CHAR('S', getFaceRegistrador(r));
    TEST_ASSERT_EQUAL_INT(45, getNumRegistrador(r));
    TEST_ASSERT_EQUAL_INT(1, getAtivoRegistrador(r));
}

void teste_getCepRegistrador(){
    TEST_ASSERT_EQUAL_STRING("cep1", getCepRegistrador(r));
}

void teste_getFaceRegistrador(){
    TEST_ASSERT_EQUAL_CHAR('S', getFaceRegistrador(r));
}

void teste_getNumRegistrador(){
    TEST_ASSERT_EQUAL_INT(45, getNumRegistrador(r));
}

void teste_getAtivoRegistrador(){
    TEST_ASSERT_EQUAL_INT(1, getAtivoRegistrador(r));
}

void teste_todasAsFaces(){
    // testa criação com cada face possível
    char faces[] = {'N', 'S', 'L', 'O'};
    for(int i = 0; i < 4; i++){
        Registrador r2 = criarRegistrador("cep2", faces[i], 10);
        TEST_ASSERT_NOT_NULL(r2);
        TEST_ASSERT_EQUAL_CHAR(faces[i], getFaceRegistrador(r2));
        liberarRegistrador(r2);
    }
}

void teste_numZero(){
    // num = 0 é válido (casa na âncora da quadra)
    Registrador r2 = criarRegistrador("cep1", 'N', 0);
    TEST_ASSERT_NOT_NULL(r2);
    TEST_ASSERT_EQUAL_INT(0, getNumRegistrador(r2));
    liberarRegistrador(r2);
}

void teste_cepDiferente(){
    Registrador r2 = criarRegistrador("cep99", 'O', 100);
    TEST_ASSERT_NOT_NULL(r2);
    TEST_ASSERT_EQUAL_STRING("cep99", getCepRegistrador(r2));
    liberarRegistrador(r2);
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarRegistrador);
    RUN_TEST(teste_getCepRegistrador);
    RUN_TEST(teste_getFaceRegistrador);
    RUN_TEST(teste_getNumRegistrador);
    RUN_TEST(teste_getAtivoRegistrador);
    RUN_TEST(teste_todasAsFaces);
    RUN_TEST(teste_numZero);
    RUN_TEST(teste_cepDiferente);
    return UNITY_END();
}