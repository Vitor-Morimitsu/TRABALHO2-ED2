# Nome do executavel
TARGET = ted

# Nome do aluno
ALUNO = vitorms

# Compilador
CC = gcc

# Flags de compilacao
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

# Diretorios
SRC_DIR   = .
UNITY_DIR = ../unity

# Flags
LIBS      = -lm
UNITY_OBJ = $(UNITY_DIR)/unity.c

# Fontes do executavel principal
MAIN_SRCS = main.c geo.c via.c qry.c quadra.c svg.c arvore.c grafo.c vertice.c aresta.c filaPrioridades.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

all: $(TARGET)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(LIBS) -o $(TARGET)

# Testes unitarios
testeArvore: testeArvore.c arvore.o quadra.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

testeQuadra: testeQuadra.c quadra.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

testeGrafo: testeGrafo.c grafo.o vertice.o aresta.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

testeVertice: testeVertice.c vertice.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

testeAresta: testeAresta.c aresta.o vertice.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

testeFilaPrioridades: testeFilaPrioridades.c filaPrioridades.o
	$(CC) $(CFLAGS) -I$(UNITY_DIR) $^ $(UNITY_OBJ) $(LIBS) -o $@
	./$@

tests: testeArvore testeQuadra testeGrafo testeVertice testeAresta testeFilaPrioridades

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
	rm -f testeArvore testeQuadra testeGrafo testeVertice testeAresta testeFilaPrioridades

pack: $(TARGET)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip -r $(ALUNO).zip $(SRC_DIR)/*.c $(SRC_DIR)/*.h Makefile LEIA-ME.txt .entrega
	rm .entrega

.PHONY: all clean pack tests testeArvore testeQuadra testeGrafo testeVertice testeAresta testeFilaPrioridades