
plotName= "conn-vs-nreq"
# inFile=   plotName.".pdata"
outFile=  plotName.".eps"

set key spacing 3.5
set key at 10,0.3
set key font "Times,24"

set term  postscript eps enhanced
set out   outFile

set grid
set xlabel "Component Size" font "Times,28"
set ylabel "Connectivity"   font "Times,28"

set ytics 0,.1,1

plot '3Tree_wOR.txt' pt 7 title 'Graph' w linespoint, \
     '1Tree_wOR.txt' pt 8 title 'Tree'  w linespoints

     


