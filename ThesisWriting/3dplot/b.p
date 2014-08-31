

plotName= "conn-vs-nreq"
# inFile=   plotName.".pdata"
outFile=  plotName.".eps"
set xlabel 'Component Size'
set ylabel 'Transmission Range'
set zlabel 'Connectivity'
set key spacing 3.5
set key at 10,0.3
set key font "Times,24"

set term  postscript eps enhanced
set out   outFile

set grid
set xlabel "Component Size" font "Times,28"
set zlabel "Connectivity"   font "Times,28"
set ylabel "Transmission Range"   font "Times,28"

set ytics 0,.25,7
set xtics  0,1,10
set ztics  0, .1,1

splot 'all.data' notitle w pm3d at s 
replot
set term wxt
pause -1 "Hit any key to continue"

