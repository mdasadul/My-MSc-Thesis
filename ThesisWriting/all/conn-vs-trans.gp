
plotName= "conn-vs-trans"
# inFile=   plotName.".pdata"
outFile=  plotName.".eps"

set key spacing 3.5
set key at 6.5,0.3
set key font "Times,24"

set term  postscript eps enhanced
set out	  outFile

#set grid lt 0 lw 0
set grid
set xlabel "Transmission Range" font "Times,28"
set ylabel "Connectivity"      font "Times,28"

set ytics 0,.1,1

#plot  '3-Tree.txt' lc 'black' pt 5 pi -0.1 title 'Graph' w linespoint, \
#      '1-Tree.txt' lc 'balck' pt 8 pi -0.5 title 'Tree'  w linespoints

plot  '3-Tree.txt' pt 5 title 'Graph' w linespoint, \
      '1-Tree.txt' pt 8 title 'Tree'  w linespoints
