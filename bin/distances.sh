../hiclures kmf $1 $3 > $1.freq
../hiclures kmf $2 $3 > $2.freq
../hiclures dst $1.freq $2.freq $3
rm $1.freq $2.freq
