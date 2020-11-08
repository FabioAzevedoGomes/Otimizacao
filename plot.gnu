set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 2 linewidth 1 \
    pointtype 2 pointsize 0.5

set xlabel "Iteration"
set ylabel "# of colors used"

plot 'bin/log.dat' with linespoints linestyle 1 title "Current State", \
     'bin/neighbors.dat' with points title "Neighbors",
