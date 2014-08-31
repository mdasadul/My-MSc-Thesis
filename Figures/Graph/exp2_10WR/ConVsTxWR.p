#set terminal postfile       (These commented lines would be used to )
#set output  "d1_plot.ps"    (generate a postscript file.            )
#set title "Connectivity vs. Transmission Range  with Relays"
set xlabel "Transmission Range"
set ylabel "Connectivity"
set grid
set key at 5,0.4
set ytics 0,.1,1
plot '1-tree_exp2_10_wR.txt' lc 'balck' pt 8 pi -0.5 title 'Tree'  w linespoints ,'3-tree_exp2_10_wR.txt'  lc 'black' pt 5 pi -0.1 title 'Graph' w linespoint
set term pdf 
set output "ConVsTx_wR.pdf"
replot
set term wxt
pause -1 "Hit any key to continue"
