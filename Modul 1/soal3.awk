LC_NUMERIC="C" awk '/Iris-setosa/ {
   split($1, col, ",");
   if (col[1] >= 5.4) {
      printf "Luas petal pada baris %d adalah %.2f\n", NR, col[3] * col[4]
   }
}' iris.data
