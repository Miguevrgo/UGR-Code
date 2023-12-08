touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/miguevr/GitHub/Programacion/Language1/dist/Debug/GNU-Linux/language1  < data/SimpleTextbigrams.txt 1> tests//.out7 2>&1"
eval $CMD
rm tests//.timeout
