for (( i=4; i <= 10; i++ )); do
    name="Viajante$i"
    sort -k2 -n Salidas/$name.txt > Salidas/temp.txt
    mv Salidas/temp.txt Salidas/$name.txt
done