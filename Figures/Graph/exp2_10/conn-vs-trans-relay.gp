
plotName= "conn-vs-Comp_woR"
# inFile=   plotName.".pdata"
outFile=  plotName.".eps"

set key spacing 3.5
set key at 6.5,0.3
set key font "Times,24"

set term  postscript eps enhanced
set out   outFile

#set grid lt 0 lw 0
set grid
set xlabel "Transmission Range" font "Times,28"
set ylabel "Connectivity"      font "Times,28"

set ytics 0,.1,1

plot '3-tree_exp2_10_wR.txt' pt 5 title 'Graph G' w linespoint, \
     '1-tree_exp2_10_wR.txt' pt 6 title 'Tree (with relays)' w linespoints, \
     '1-Tree.txt'            pt 8 title 'Tree (no relays)'  w linespoints


plot '1Tree_wOR.txt' lc 'balck' pt 8 pi -0.5 title '1-tree'  w linespoints ,'2Tree_wOR.txt' lc 'red' pt 5 pi -0.1 title '2-tree'  w linespoints,'3Tree_wOR.txt'  lc 'black' pt 6 pi -0.1 title '3-tree' w linespoint

