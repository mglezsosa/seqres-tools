../seqres writeo $1 $2 $2.occ
../seqres writeo $1 $3 $3.occ
sort -n -k 1 $2.occ -o $2.ord
sort -n -k 1 $3.occ -o $3.ord
../seqres collapse $2.ord
../seqres collapse $3.ord
../seqres hits $2.ord_collapse $3.ord_collapse $4
rm $2.occ $3.occ $2.ord $3.ord $2.ord_collapse $3.ord_collapse
