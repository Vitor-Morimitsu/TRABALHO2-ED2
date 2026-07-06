#!/bin/bash
# =============================================================================
# run_valgrind.sh — Roda todos os testes do t2 com valgrind --leak-check=full
# Execute dentro do WSL a partir da pasta src/:
#   bash run_valgrind.sh
# =============================================================================

set -e   # para na primeira falha de compilação

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$SCRIPT_DIR"
T2_DIR="$SCRIPT_DIR/../testes/t2"
OUT_DIR="$SCRIPT_DIR/../testes/output"
TED="$SRC_DIR/ted"

# Cores para output
RED='\033[0;31m'
GRN='\033[0;32m'
YLW='\033[1;33m'
BLU='\033[0;34m'
NC='\033[0m'

# --------------------------------------------------------------------------
echo -e "${BLU}=== Limpando e recompilando ===${NC}"
cd "$SRC_DIR"
make clean
make ted
echo -e "${GRN}Compilação OK${NC}\n"

mkdir -p "$OUT_DIR"

# --------------------------------------------------------------------------
TOTAL=0
ERROS=0
LEAKS=0

run_valgrind() {
    local caso="$1"    # ex: c1
    local geo="$2"     # caminho do .geo
    local via="$3"     # caminho do .via
    local qry="$4"     # caminho do .qry

    local nome_qry
    nome_qry="$(basename "$qry" .qry)"

    echo -e "${YLW}--- [$caso] $nome_qry ---${NC}"

    local log
    log=$(valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --error-exitcode=1 \
        "$TED" -f "$geo" -v "$via" -q "$qry" -o "$OUT_DIR" 2>&1)

    local exit_code=$?
    TOTAL=$((TOTAL + 1))

    # Verifica leak summary
    local definitely lost
    definitely=$(echo "$log" | grep "definitely lost:" | grep -v ": 0 bytes" || true)
    local indirectly lost
    indirectly=$(echo "$log" | grep "indirectly lost:" | grep -v ": 0 bytes" || true)

    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}  ✗ FALHOU (exit $exit_code)${NC}"
        echo "$log" | grep -E "ERROR SUMMARY|definitely lost|indirectly lost|Invalid|Uninitialised" || true
        ERROS=$((ERROS + 1))
    else
        # Verifica se há leaks mesmo sem exit code de erro
        local leak_summary
        leak_summary=$(echo "$log" | grep "definitely lost:" || true)
        if echo "$leak_summary" | grep -qv ": 0 bytes in 0 blocks"; then
            echo -e "${RED}  ⚠ leak detectado${NC}"
            echo "$log" | grep -E "definitely lost|indirectly lost"
            LEAKS=$((LEAKS + 1))
        else
            echo -e "${GRN}  ✓ OK — sem leaks${NC}"
        fi
    fi
    echo ""
}

# --------------------------------------------------------------------------
echo -e "${BLU}=== Rodando testes com Valgrind ===${NC}\n"

for caso in c1 c2 c3; do
    geo="$T2_DIR/${caso}.geo"
    via="$T2_DIR/${caso}-v.via"
    qry_dir="$T2_DIR/${caso}"

    if [ ! -f "$geo" ] || [ ! -f "$via" ]; then
        echo -e "${RED}Arquivos $geo ou $via não encontrados, pulando $caso${NC}"
        continue
    fi

    for qry in "$qry_dir"/*.qry; do
        [ -f "$qry" ] || continue
        run_valgrind "$caso" "$geo" "$via" "$qry"
    done
done

# --------------------------------------------------------------------------
echo -e "${BLU}=== Resumo ===${NC}"
echo -e "Total de testes : $TOTAL"
echo -e "Falhas (exit)   : ${RED}$ERROS${NC}"
echo -e "Leaks detectados: ${RED}$LEAKS${NC}"

if [ $ERROS -eq 0 ] && [ $LEAKS -eq 0 ]; then
    echo -e "\n${GRN}✓ Todos os testes passaram sem leaks!${NC}"
else
    echo -e "\n${RED}✗ Há problemas a corrigir.${NC}"
    exit 1
fi
