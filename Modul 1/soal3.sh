awk -F "," '
BEGIN {printf "Hasil Luas\n"; n=0;}
{n++}
/Iris-setosa/{
	luas=$3*$4;
	if($1>=5.4) {
	   printf "Luas petal pada baris %d adalah %.2f\n", n, luas
	}
}' iris.data
