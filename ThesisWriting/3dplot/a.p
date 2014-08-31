set xlabel 'Component Size'
set ylabel 'Transmission Range'
set zlabel 'Connectivity'
set samples 51, 51
set isosamples 21, 21
set ytics 0,.25,7
set xtics  0,1,10
set ztics  0, .1,1
splot 'a.data'   pt 8 pi 150 notitle w linespoints,'b.data'   pt 8 pi 150 notitle   w linespoints,'c.data'   pt 8 pi 150 notitle w linespoints,'d.data'   pt 8 pi 150 notitle w linespoints,'e.data'   pt 8 pi 150 notitle w linespoints,'f.data'   pt 8 pi 150 notitle w linespoints,'g.data'   pt 8 pi 150 notitle w linespoints,'h.data'   pt 8 pi 150 notitle w linespoints,'i.data'   pt 8 pi 150 notitle w linespoints,'j.data'   pt 8 pi 150 notitle w linespoints,'k.data'   pt 8 pi 150 notitle w linespoints
set term pdf 
set output "a.pdf"
replot
set term wxt
pause -1 "Hit any key to continue"
