#include "filaPrioridades.h"
#include "unity.h"

FilaPrioridades fila;

void setUp(){
    fila = criarFilaDePrioridade();
}

void tearDown(){
    liberarFila(fila);
}

void teste_criarFila(){
    TEST_ASSERT_NOT_NULL(fila);
}

void teste_filaVaziaAoCriar(){
    // recém criada deve estar vazia
    TEST_ASSERT_EQUAL_INT(0, verificarFilaVazia(fila));
}

void teste_inserirUmElemento(){
    inserirFilaPrioridades(fila, 0, 5.0);
    // agora deve conter elementos
    TEST_ASSERT_EQUAL_INT(1, verificarFilaVazia(fila));
}

void teste_ordemPrioridade(){
    // insere fora de ordem
    inserirFilaPrioridades(fila, 2, 10.0);
    inserirFilaPrioridades(fila, 0, 1.0);
    inserirFilaPrioridades(fila, 1, 5.0);

    // o topo deve ser sempre o menor parâmetro
    TEST_ASSERT_EQUAL_INT(0, getIdVerticeTopo(fila));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, getParametroTopo(fila));
}

void teste_removerElemento(){
    inserirFilaPrioridades(fila, 0, 1.0);
    inserirFilaPrioridades(fila, 1, 5.0);

    // remove o menor (0, 1.0)
    removerFilaPrioridades(fila);

    // agora o topo deve ser (1, 5.0)
    TEST_ASSERT_EQUAL_INT(1, getIdVerticeTopo(fila));
    TEST_ASSERT_EQUAL_DOUBLE(5.0, getParametroTopo(fila));
}

void teste_filaVaziaAposRemoverTudo(){
    inserirFilaPrioridades(fila, 0, 1.0);
    inserirFilaPrioridades(fila, 1, 5.0);

    removerFilaPrioridades(fila);
    removerFilaPrioridades(fila);

    // deve estar vazia novamente
    TEST_ASSERT_EQUAL_INT(0, verificarFilaVazia(fila));
}

void teste_removerFilaVazia(){
    // não deve crashar
    removerFilaPrioridades(fila);
}

void teste_inserirMuitosElementos(){
    // testa com vários elementos para garantir a ordenação
    inserirFilaPrioridades(fila, 4, 40.0);
    inserirFilaPrioridades(fila, 2, 20.0);
    inserirFilaPrioridades(fila, 0, 0.0);
    inserirFilaPrioridades(fila, 3, 30.0);
    inserirFilaPrioridades(fila, 1, 10.0);

    // remove um por um e verifica a ordem crescente
    double esperado[] = {0.0, 10.0, 20.0, 30.0, 40.0};
    int ids[]         = {0,   1,    2,    3,    4};

    for(int i = 0; i < 5; i++){
        TEST_ASSERT_EQUAL_INT(ids[i], getIdVerticeTopo(fila));
        TEST_ASSERT_EQUAL_DOUBLE(esperado[i], getParametroTopo(fila));
        removerFilaPrioridades(fila);
    }
}

int main(){
    UNITY_BEGIN();
    RUN_TEST(teste_criarFila);
    RUN_TEST(teste_filaVaziaAoCriar);
    RUN_TEST(teste_inserirUmElemento);
    RUN_TEST(teste_ordemPrioridade);
    RUN_TEST(teste_removerElemento);
    RUN_TEST(teste_filaVaziaAposRemoverTudo);
    RUN_TEST(teste_removerFilaVazia);
    RUN_TEST(teste_inserirMuitosElementos);
    return UNITY_END();
}