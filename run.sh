#!/bin/bash

./seq_bubble > s_bubble.txt
./seq_qsort > s_qsort.txt
mpirun -np 3 bubble > bubble2.txt
mpirun -np 5 bubble > bubble4.txt
mpirun -np 9 bubble > bubble8.txt
mpirun -np 17 bubble > bubble16.txt
mpirun -np 33 bubble > bubble32.txt
mpirun -np 65 bubble > bubble64.txt
mpirun -np 129 bubble > bubble128.txt
mpirun -np 3 qsort > qsort2.txt
mpirun -np 5 qsort > qsort4.txt
mpirun -np 9 qsort > qsort8.txt
mpirun -np 17 qsort > qsort16.txt
mpirun -np 33 qsort > qsort32.txt
mpirun -np 65 qsort > qsort64.txt
mpirun -np 129 qsort > qsort128.txt
