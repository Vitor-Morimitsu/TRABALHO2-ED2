# Nome do executavel
TARGET = ted

# Nome do aluno
ALUNO = vitorms

# Compilador
CC = gcc

# Flags de compilacao
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb -I../include

# Diretorios
SRC_DIR   = .
UNITY_DIR = ../testes/unity

# Flags
LIBS      = -lm
UNITY_OBJ = $(UNITY_DIR)/unity.c

# Fontes do executavel principal
MAIN_SRCS = main.c geo.c via.c qry.c quadra.c svg.c arvore.c grafo.c vertice.c aresta.c filaPrioridades.c registrador.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

all: $(TARGET)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBS) -o $(TARGET)

# Testes unitarios
TEST_DIR = ../testes

teste_arvore: $(TEST_DIR)/teste_arvore.c arvore.o quadra.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

teste_grafo: $(TEST_DIR)/teste_grafo.c grafo.o vertice.o aresta.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

teste_Vertice: $(TEST_DIR)/teste_Vertice.c vertice.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

teste_aresta: $(TEST_DIR)/teste_aresta.c aresta.o vertice.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

teste_filaPrioridades: $(TEST_DIR)/teste_filaPrioridades.c filaPrioridades.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

teste_registrador: $(TEST_DIR)/teste_registrador.c registrador.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $(TEST_DIR)/$@
	$(TEST_DIR)/$@

tests: teste_arvore teste_grafo teste_Vertice teste_aresta teste_filaPrioridades teste_registrador

clean:
	-rm -f $(SRC_DIR)/*.o $(TARGET)
	-rm -f $(TEST_DIR)/teste_arvore* $(TEST_DIR)/teste_grafo* $(TEST_DIR)/teste_Vertice* $(TEST_DIR)/teste_aresta* $(TEST_DIR)/teste_filaPrioridades* $(TEST_DIR)/teste_registrador*

pack: $(TARGET)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip -r $(ALUNO).zip $(SRC_DIR)/*.c $(SRC_DIR)/*.h Makefile LEIA-ME.txt .entrega
	rm .entrega

.PHONY: all clean pack tests teste_arvore teste_grafo teste_Vertice teste_aresta teste_filaPrioridades teste_registrador