../seqres kmf $2 $1 > $2.freq
../seqres kmf $3 $1 > $3.freq
../seqres dst $2.freq $3.freq $1
rm $2.freq $3.freq
