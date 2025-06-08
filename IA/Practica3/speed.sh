#!/bin/bash

if [ -z "$1" ]; then
    echo "Uso: $0 <id> <ninja_numbers>"
    echo "  ninja_numbers: uno o más números separados por espacios (1 2 3), o ALL para todos"
    exit 1
fi

id="$1"
shift

if [ $# -eq 0 ]; then
    echo "Error: Debes especificar al menos un ninja o ALL"
    exit 1
fi

declare -a ninjas=()

if [[ "$@" == "ALL" ]]; then
    ninjas=(1 2 3)
else
    for arg in "$@"; do
        if [[ "$arg" =~ ^[123]$ ]]; then
            ninjas+=("$arg")
        else
            echo "Advertencia: Ninja inválido '$arg' ignorado. Solo se permiten 1, 2, 3 o ALL."
        fi
    done
fi

if [ ${#ninjas[@]} -eq 0 ]; then
    echo "No se especificaron ninjas válidos. Abortando."
    exit 1
fi

# Crear el directorio de logs si no existe
mkdir -p ./logs

# Copiar el código fuente actual del jugador IA a la carpeta de logs
ai_src="$HOME/GitHub/practica3/src/personal/AIPlayer.cpp"
timestamp=$(date +%Y-%m-%d_%H-%M-%S)
cp --preserve=timestamps "$ai_src" "./logs/personal/AIPlayer_${timestamp}.cpp"

ganadas=0

output_file="./logs/id${id}_${timestamp}.log"
win_file=$(mktemp /tmp/tmp.parchisXXXXXX.win)
echo "Ejecución de partidas con el ID: $id" >>"$output_file"
echo "Ejecución de partidas con el ID: $id"

for ninja in "${ninjas[@]}"; do
    for pos in 1 2; do
        (
            echo "Ejecutando Ninja $ninja contra jugador $pos..."
            logfile=$(mktemp /tmp/tmp.parchisXXXXXX)

            if [ "$pos" -eq 1 ]; then
                ./ParchisGame --p1 AI "$id" Yo --p2 NINJA "$ninja" N --no-gui >"$logfile" 2>&1
            else
                ./ParchisGame --p2 AI "$id" Yo --p1 NINJA "$ninja" N --no-gui >"$logfile" 2>&1
            fi

            echo "Resultado ejecución para Ninja $ninja contra jugador $pos:"
            echo "Resultado ejecución para Ninja $ninja contra jugador $pos:" >>"$output_file"
            if tail -n 5 "$logfile" | grep -q "Yo"; then
                echo "✔️ ¡He ganado! 🎉"
                echo "✔️ ¡He ganado! 🎉" >>"$output_file"
                echo "WIN" >>"$win_file"
            else
                echo "❌ He perdido. 😞"
                echo "❌ He perdido. 😞" >>"$output_file"
            fi
            echo "Fin de ejecución Ninja $ninja contra jugador $pos"
        ) &
        sleep 0.3
    done
done

wait
echo "Todas las partidas han finalizado."

ganadas=$(wc -l <"$win_file")
rm -f "$win_file" # limpia el tmp

echo "He ganado $ganadas veces."

if [ "$ganadas" -le 3 ]; then
    echo "Menos de 4 victorias: se borra el log $output_file"
    rm -f "$output_file"
else
    echo "He ganado $ganadas veces." >>"$output_file"
fi
