#include "svg.h"

void abrirSvg(FILE* arqSvg){
    if(arqSvg == NULL){
        printf("Erro em abrirSvg\n");
    }
    fprintf(arqSvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" "
            "xmlns=\"http://www.w3.org/2000/svg\" "
            "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
            "version=\"1.1\" width=\"18000\" height=\"5000\">\n");
}

void desenharRetanguloSVG(FILE* arqSvg, Quadra q){
    if(!arqSvg || !q){
        printf("Erro em desenharRetanguloSVG\n");
        return;
    }
    fprintf(arqSvg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1\" />\n",
            getXQuadra(q),getYQuadra(q),getWQuadra(q),getHQuadra(q), getCfillQuadra(q), getCstrkQuadra(q));
}

//coloca um x no local da ancora da quadra removida
void comandoRqSvg(FILE* svg, float x, float y, float w, float h){
    if(!svg){
        printf("Erro em comandoRqSvg\n");
        return;
    }
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"2\" />\n", x, y, x+w, y+h);
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"2\" />\n", x+w, y, x, y+h);
}

void comandoMudSvg(FILE* svg, float x, float y, float w, float h, char face, char* cpf){
    if(!svg){
        printf("Erro em comandoMudSvg\n");
        return;
    }
    /* Rosa dos ventos INVERTIDA: N=baixo, S=cima, L=esquerda, O=direita */
    float mx, my;
    float lado = 12.0f; /* tamanho do quadradinho marcador */
    if(face == 'N' || face == 'n') {
        /* face Norte = borda inferior da quadra */
        mx = x + w / 2.0f;
        my = y + h;
    } else if(face == 'S' || face == 's') {
        /* face Sul = borda superior */
        mx = x + w / 2.0f;
        my = y;
    } else if(face == 'L' || face == 'l') {
        /* face Leste = borda esquerda */
        mx = x;
        my = y + h / 2.0f;
    } else { /* face O */
        /* face Oeste = borda direita */
        mx = x + w;
        my = y + h / 2.0f;
    }
    fprintf(svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"red\" stroke=\"darkred\" stroke-width=\"1\" />\n",
            mx - lado/2.0f, my - lado/2.0f, lado, lado);
    if(cpf) fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"3\" text-anchor=\"middle\" dominant-baseline=\"middle\">%s</text>\n",
            mx, my, cpf);
}

//coloca uma cruz vermelha no local do endereço
void comandoRipSvg(FILE* svg,float x, float y){
    if(!svg){
        printf("Erro em comandoRipSvg\n");
        return;
    }
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"4\" />\n", x, y-20, x, y+20);
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"red\" stroke-width=\"4\" />\n", x-20, y, x+20, y);
}

//colocar numero de moradores em cada face da quadra e na quadra como um todo no centro
void comandoPqSvg(FILE* svg, Quadra q, int total, int n, int s, int l, int o){
    if(!svg || !q){
        printf("Erro em comandoPqSvg\n");
        return;
    }
    float qx = getXQuadra(q);
    float qy = getYQuadra(q);
    float qw = getWQuadra(q);
    float qh = getHQuadra(q);

    // -- TOTALIZADOR: Bem no centro da quadra (x + metade da largura)
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"black\" font-size=\"14\">Total: %d</text>\n", 
            qx + (qw/2), qy + (qh/2), total);
    
    // -- NORTE: Inferior da quadra (Eixo Y cresce, base da tela)
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"14\">%d</text>\n", 
            qx + (qw/2), qy + qh + 10, n);
            
    // -- SUL: Superior da quadra (Eixo Y menor, topo da tela)
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"14\">%d</text>\n", 
            qx + (qw/2), qy - 10, s);
            
    // -- LESTE: Esquerda da quadra (Eixo X menor)
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"14\">%d</text>\n", 
            qx - 15, qy + (qh/2), l);
            
    // -- OESTE: Direita da quadra (Eixo X cresce)
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"red\" font-size=\"14\">%d</text>\n", 
            qx + qw + 5, qy + (qh/2), o);
}

//vai desenhar um círculo preto no local do despejo
void comandoDspjSvg(FILE* svg, float x, float y){
    if(!svg){
        printf("Erro em comandoDspjSvg\n");
        return; 
    }
    fprintf(svg, "<circle cx=\"%f\" cy=\"%f\" r=\"15\" fill=\"black\" />\n", x, y);
}

void svgComandoP(FILE* arqSvg){
    (void)arqSvg; /* o caminho é desenhado segmento a segmento via svgDesenharSegmentoRua */
}

/* Linha vertical pontilhada vermelha do endereço ao topo da página + rótulo do registrador */
void svgComandoO(FILE* svg, double x, double y, int numRegistrador) {
    if (!svg) return;
    fprintf(svg, "<line x1=\"%f\" y1=\"0\" x2=\"%f\" y2=\"%f\" "
            "stroke=\"red\" stroke-width=\"1\" stroke-dasharray=\"6,4\" />\n", x, x, y);
    fprintf(svg, "<text x=\"%f\" y=\"14\" fill=\"red\" font-size=\"11\" "
            "text-anchor=\"middle\">R%d</text>\n", x, numRegistrador);
}

/* Bounding box de componente conexo — retângulo colorido com 50% de transparência */
void svgComandoRegs(FILE* svg, double minX, double minY, double maxX, double maxY, const char* cor) {
    if (!svg) return;
    
    if (maxX - minX < 5.0) {
        minX -= 5.0;
        maxX += 5.0;
    }
    if (maxY - minY < 5.0) {
        minY -= 5.0;
        maxY += 5.0;
    }
    
    double bw = maxX - minX;
    double bh = maxY - minY;
    fprintf(svg, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" "
            "fill=\"%s\" fill-opacity=\"0.5\" "
            "stroke=\"%s\" stroke-width=\"1\" />\n", minX, minY, bw, bh, cor, cor);
}

/* Aresta selecionada pelo comando exp — linha vermelha grossa */
void svgComandoExp(FILE* svg, double x1, double y1, double x2, double y2) {
    if (!svg) return;
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
            "stroke=\"red\" stroke-width=\"4\" />\n", x1, y1, x2, y2);
}

/* Segmento de rua do caminho mínimo — linha colorida e ligeiramente grossa */
void svgDesenharSegmentoRua(FILE* svg, double x1, double y1, double x2, double y2, char* cor) {
    if (!svg || !cor) return;
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" "
            "stroke=\"%s\" stroke-width=\"3\" stroke-linecap=\"round\" />\n",
            x1, y1, x2, y2, cor);
}

/* Marcador de início (I) ou fim (F) do caminho — círculo colorido com letra */
void svgDesenharMarcadorCaminho(FILE* svg, double x, double y, char letra, char* cor) {
    if (!svg || !cor) return;
    fprintf(svg, "<circle cx=\"%f\" cy=\"%f\" r=\"10\" "
            "fill=\"%s\" stroke=\"white\" stroke-width=\"1.5\" />\n", x, y, cor);
    fprintf(svg, "<text x=\"%f\" y=\"%f\" fill=\"white\" font-size=\"11\" font-weight=\"bold\" "
            "text-anchor=\"middle\" dominant-baseline=\"middle\">%c</text>\n", x, y, letra);
}

/* Desenha o caminho como <path> animado:
 * — linha colorida com id 'animId'
 * — ponto (circulo) percorrendo o trajeto em loop por 'durSegundos' segundos */
void svgAnimarCaminho(FILE* svg, double* xs, double* ys, int n,
                      char* corLinha, char* corPonto,
                      double durSegundos, char* animId) {
    if (!svg || !xs || !ys || n < 2 || !animId) return;

    /* Linha do caminho (path com id para servir de trilho da animacao) */
    fprintf(svg, "<path id=\"%s\" d=\"M %.2f,%.2f", animId, xs[0], ys[0]);
    for (int i = 1; i < n; i++)
        fprintf(svg, " L %.2f,%.2f", xs[i], ys[i]);
    fprintf(svg, "\" fill=\"none\" stroke=\"%s\" stroke-width=\"3\" "
            "stroke-linecap=\"round\" stroke-linejoin=\"round\"/>\n", corLinha);

    /* Ponto animado percorrendo o path */
    fprintf(svg, "<circle r=\"8\" fill=\"%s\" stroke=\"white\" stroke-width=\"2\">\n",
            corPonto);
    fprintf(svg, "  <animateMotion dur=\"%.1fs\" repeatCount=\"indefinite\" "
            "calcMode=\"linear\" rotate=\"auto\">\n", durSegundos);
    fprintf(svg, "    <mpath xlink:href=\"#%s\"/>\n", animId);
    fprintf(svg, "  </animateMotion>\n");
    fprintf(svg, "</circle>\n");
}

void fecharSVG(FILE* arqSvg){
    if(!arqSvg){
        printf("Erro em fecharSvg\n");
        return;
    }
    fprintf(arqSvg, "</svg>\n");
}
