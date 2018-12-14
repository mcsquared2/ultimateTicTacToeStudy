#!/bin/bash
games=1000
for counter in 1 2 4 8 16
do 
	time mpirun -np $counter a.out -g $games > data/monte_$counter.p.$games.g.100.gpm.out
done
echo "All Done"
exit 0
