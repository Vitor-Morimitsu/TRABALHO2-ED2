#include "qry.h"
#include "filaPrioridades.h"
#include <string.h>

void comandoO(FILE* svg, FILE* txt, int numRegistrador, char* cep, char face, int num, Arvore quadras, Registrador regs[]){
    Quadra q = buscarArvore(cep, quadras);
    if(q == NULL){ printf("Quadra não encontrada\n"); return; }

    float x = getXQuadra(q), y = getYQuadra(q);
    float w = getWQuadra(q), h = getHQuadra(q);

    double px, py;
    if(face == 'S' || face == 's')      { px = (x+w) - num; py = y;   }
    else if(face == 'N' || face == 'n') { px = (x+w) - num; py = y+h; }
    else if(face == 'L' || face == 'l') { px = x;           py = (y+h) - num; }
    else                                { px = x+w;          py = (y+h) - num; }

    setCepRegistrador(regs[numRegistrador], cep);
    setFaceRegistrador(regs[numRegistrador], face);
    setNumRegistrador(regs[numRegistrador], num);
    ativarRegistrador(regs[numRegistrador]);

    svgComandoO(svg, px, py, numRegistrador);
    fprintf(txt, "R%d: cep=%s face=%c num=%d coord=(%.2f, %.2f)\n",numRegistrador, cep, face, num, px, py);
}

void comandoMvm(Grafo grafo, double velocidadeNova, double x, double y, double w, double h){
    int n = getNumVerticesGrafo(grafo);
    for(int i = 0; i < n; i++){
        // verifica se o vértice de origem está dentro da região
        Vertice vOrigem = getVerticeGrafo(grafo, i);
        double vx = getXVertice(vOrigem);
        double vy = getYVertice(vOrigem);

        if(vx >= x && vx <= x+w && vy >= y && vy <= y+h){
            // origem está dentro — atualiza todas as arestas saindo desse vértice
            void* cel = getPrimeiraArestaGrafo(grafo, i);
            while(cel != NULL){
                Aresta a = getDadosAresta(cel);
                setVmAresta(a, velocidadeNova);
                cel = getProximaAresta(cel);
            }
        }
    }
}

void comandoRegs(FILE* txt, FILE* svg, Arvore quadras, Grafo grafo, double vInsuficiente){
    (void)quadras; /* reservado para uso futuro */
    //considera insuficiente os trechos com velocidade vInsuficiente
    int contador = 0;
    int n = getNumVerticesGrafo(grafo);
    for(int i = 0; i < n; i++){
        void* cel = getPrimeiraArestaGrafo(grafo, i);
        while(cel != NULL){
            Aresta a   = getDadosAresta(cel);
            double vAntiga = getVmAresta(a);
            if(vAntiga < vInsuficiente){
                contador++;
                calcularBoundingBox(svg, a);
            }
            cel = getProximaAresta(cel);
        }
    }
    fprintf(txt,"Quantidade de ruas com velocidade insuficiente : %d\n", contador);

}

void calcularBoundingBox(FILE* svg,Aresta a){
    if(a == NULL){
        printf("Erro em calcularBoundingBox\n");
        return;
    }
    Vertice v1 = getVerticeV1(a);
    double x1 = getXVertice(v1);
    double y1 = getYVertice(v1);

    Vertice v2 = getVerticeV2(a);
    double x2 = getXVertice(v2);
    double y2 = getYVertice(v2);

    svgComandoRegs(svg,x1,y1, x2,y2);
}

void comandoExp(FILE* svg, Grafo grafo, Arvore quadras, double velocidade){
    (void)quadras; /* reservado para uso futuro */
    int n = getNumVerticesGrafo(grafo);
    for(int i = 0; i < n; i++){
        void* cel = getPrimeiraArestaGrafo(grafo, i);
        while(cel != NULL){
            Aresta a = getDadosAresta(cel);
            Vertice v1 = getVerticeV1(a);
            Vertice v2 = getVerticeV2(a);
            double vAntiga = getVmAresta(a);
            if(vAntiga < velocidade){
                setVmAresta(a, vAntiga * 1.5);
                svgComandoExp(svg, getXVertice(v1), getYVertice(v1),getXVertice(v2), getYVertice(v2));
            }
            cel = getProximaAresta(cel);
        }
    }
}

/* -----------------------------------------------------------------------
 * Funções auxiliares para o Dijkstra (comando p?)
 * -----------------------------------------------------------------------*/

/* Calcula a posição geográfica (px,py) de um registrador a partir da quadra */
static void getPosicaoRegistrador(Registrador r, Arvore quadras, double* px, double* py) {
    char* cep  = getCepRegistrador(r);
    char  face = getFaceRegistrador(r);
    int   num  = getNumRegistrador(r);

    Quadra q = (Quadra)buscarArvore(cep, quadras);
    if (q == NULL) { *px = 0.0; *py = 0.0; return; }

    float x = getXQuadra(q), y = getYQuadra(q);
    float w = getWQuadra(q), h = getHQuadra(q);

    if      (face == 'S' || face == 's') { *px = (x + w) - num; *py = y;          }
    else if (face == 'N' || face == 'n') { *px = (x + w) - num; *py = y + h;      }
    else if (face == 'L' || face == 'l') { *px = x;             *py = (y + h) - num; }
    else                                  { *px = x + w;         *py = (y + h) - num; }
}

/* Retorna o índice do vértice mais próximo de (px,py) no grafo */
static int encontrarVerticeProximo(Grafo grafo, double px, double py) {
    int n       = getNumVerticesGrafo(grafo);
    int nearest = 0;
    double minD = -1.0;

    for (int i = 0; i < n; i++) {
        Vertice v = getVerticeGrafo(grafo, i);
        double dx = getXVertice(v) - px;
        double dy = getYVertice(v) - py;
        double d  = dx * dx + dy * dy;
        if (minD < 0.0 || d < minD) { minD = d; nearest = i; }
    }
    return nearest;
}

/* Algoritmo de Dijkstra.
 * Preenche dist[] (distância mínima de 'origem' a cada vértice) e
 * pred[] (predecessor no caminho mínimo). Usa comprimento da aresta como custo. */
static void dijkstra(Grafo grafo, int origem, double* dist, int* pred) {
    int n = getNumVerticesGrafo(grafo);

    for (int i = 0; i < n; i++) { dist[i] = 1e18; pred[i] = -1; }
    dist[origem] = 0.0;

    FilaPrioridades fila = criarFilaDePrioridade();
    inserirFilaPrioridades(fila, origem, 0.0);

    while (verificarFilaVazia(fila) != 0) {   /* != 0 → fila não vazia */
        int    u  = getIdVerticeTopo(fila);
        double du = getParametroTopo(fila);
        removerFilaPrioridades(fila);

        if (du > dist[u]) continue;           /* entrada desatualizada */

        void* cel = getPrimeiraArestaGrafo(grafo, u);
        while (cel != NULL) {
            int    v    = getDestinoAresta(cel);
            Aresta a    = getDadosAresta(cel);
            double peso = getCmpAresta(a);    /* custo = comprimento em metros */

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                inserirFilaPrioridades(fila, v, dist[v]);
            }
            cel = getProximaAresta(cel);
        }
    }
    liberarFila(fila);
}

/* Calcula e desenha o menor caminho entre dois registradores.
 * cc = cor das arestas do caminho, cr = cor dos marcadores I/F */
void comandoP(FILE* svg, FILE* txt, Arvore quadras, Grafo grafo,
              Registrador reg1, Registrador reg2, char* cc, char* cr) {
    if (!getAtivoRegistrador(reg1) || !getAtivoRegistrador(reg2)) {
        printf("Registrador inativo em comandoP\n");
        return;
    }

    /* Posições geográficas dos registradores */
    double px1, py1, px2, py2;
    getPosicaoRegistrador(reg1, quadras, &px1, &py1);
    getPosicaoRegistrador(reg2, quadras, &px2, &py2);

    /* Vértices mais próximos de cada posição */
    int idxStart = encontrarVerticeProximo(grafo, px1, py1);
    int idxEnd   = encontrarVerticeProximo(grafo, px2, py2);

    int n = getNumVerticesGrafo(grafo);
    double* dist = malloc(n * sizeof(double));
    int*    pred = malloc(n * sizeof(int));
    if (!dist || !pred) {
        printf("Erro ao alocar memoria em comandoP\n");
        free(dist); free(pred); return;
    }

    dijkstra(grafo, idxStart, dist, pred);

    /* Verifica alcançabilidade */
    if (dist[idxEnd] >= 1e17) {
        fprintf(txt, "Caminho entre R%d e R%d: nao encontrado\n",
                getNumRegistrador(reg1), getNumRegistrador(reg2));
        free(dist); free(pred); return;
    }

    /* Reconstrói o caminho via array de predecessores */
    int* caminho = malloc(n * sizeof(int));
    if (!caminho) { free(dist); free(pred); return; }
    int tam = 0;
    for (int v = idxEnd; v != -1; v = pred[v]) {
        caminho[tam++] = v;
        if (tam > n) break;  /* segurança contra ciclos */
    }
    /* Inverte para ordem origem → destino */
    for (int i = 0, j = tam - 1; i < j; i++, j--) {
        int tmp = caminho[i]; caminho[i] = caminho[j]; caminho[j] = tmp;
    }

    /* Desenha cada segmento do caminho no SVG com a cor cc */
    for (int i = 0; i < tam - 1; i++) {
        Vertice va = getVerticeGrafo(grafo, caminho[i]);
        Vertice vb = getVerticeGrafo(grafo, caminho[i + 1]);
        svgDesenharSegmentoRua(svg,
            getXVertice(va), getYVertice(va),
            getXVertice(vb), getYVertice(vb), cc);
    }

    /* Marcadores de início (I) e fim (F) com a cor cr */
    Vertice vS = getVerticeGrafo(grafo, idxStart);
    Vertice vE = getVerticeGrafo(grafo, idxEnd);
    svgDesenharMarcadorCaminho(svg, getXVertice(vS), getYVertice(vS), 'I', cr);
    svgDesenharMarcadorCaminho(svg, getXVertice(vE), getYVertice(vE), 'F', cr);

    /* Saída textual */
    fprintf(txt, "Caminho: ");
    for (int i = 0; i < tam; i++) {
        Vertice v = getVerticeGrafo(grafo, caminho[i]);
        fprintf(txt, "%s%s", getIDVertice(v), (i < tam - 1) ? " -> " : "");
    }
    fprintf(txt, "\nComprimento total: %.2f metros\n", dist[idxEnd]);

    free(dist); free(pred); free(caminho);
}

/* -----------------------------------------------------------------------*/

void lerQry(FILE* qry, FILE* svg, FILE* txt, Arvore quadras, Grafo grafo, Registrador regs[]){
    if (qry == NULL || svg == NULL || txt == NULL || quadras == NULL || grafo == NULL){
        printf("Erro em lerQry\n");
        return;
    }
    char linha[256];
    char comando[256];
    while(fgets(linha, sizeof(linha), qry) != NULL){
        if (linha[0] == '\n' || linha[0] == '#') continue;

        int lidos_cmd = sscanf(linha, "%9s", comando);
        if (lidos_cmd != 1) continue;
        if(strcmp(comando, "@o?") == 0){
            //armazena a posição geográfica do endereço cep/face/num no registrador reg 
            int numRegistrador;
            char cep[32];
            char face;
            int num;
            int lidos = sscanf(&linha[strlen(comando)], " R%d %31s %c %d", &numRegistrador, cep, &face, &num);
            if(lidos != 4){
                printf("Erro ao ler @0?\n");
                continue;
            }
            comandoO(svg, txt, numRegistrador, cep, face, num, quadras, regs);

        }else if(strcmp(comando, "mvm") == 0){
            // atualiza a velocidade média das aresta dentro da região (x,y,w,h) para v
            double x, y, w, h, v;
            int lidos = sscanf(&linha[strlen(comando)], " %lf %lf %lf %lf %lf", &v,&x,&y,&w,&h);
            if(lidos != 5){
                printf("Erro ao ler mvm\n");
                continue;
            }
            comandoMvm(grafo,v,x,y,w,h);

        }else if(strcmp(comando, "regs") == 0){
            double v1;
            int lidos = sscanf(&linha[strlen(comando)], " %lf", &v1);
            if(lidos != 1){
                printf("Erro ao ler regs\n");
                continue;
            }
            comandoRegs(txt,svg, quadras, grafo,v1);

        }else if(strcmp(comando, "exp") == 0){
            double v1;
            int lidos = sscanf(&linha[strlen(comando)], " %lf", &v1);
            if(lidos != 1){
                printf("Erro ao ler exp\n");
                continue;
            }
            comandoExp(svg, grafo, quadras, v1);

        }else if(strcmp(comando, "p?") == 0){
            int reg1, reg2;
            char cc[32];
            char cr[32];
            int lidos = sscanf(&linha[strlen(comando)], " R%d R%d %31s %31s", &reg1, &reg2, cc, cr);
            if(lidos != 4){
                printf("Erro ao ler p?\n");
                continue;
            }
            comandoP(svg, txt, quadras, grafo, regs[reg1], regs[reg2], cc, cr);

        }else {
            printf("Erro ao ler o qry. Nenhum comando encontrado\n");
            continue;
        }
    }
}
