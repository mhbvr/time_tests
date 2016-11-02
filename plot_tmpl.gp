#set terminal png size $size noenhanced transparent interlace font 'Liberation Sans,9'
set terminal svg size 512,512 font 'Liberation Sans,9'
set output 'plot.svg'

# Ticks style 
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror

# Grid style
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

# Сolor definitions
# 1, 2 - actual series data
# 9 - area between min and max
# 10 - border of area between min and max

set style line 1 lc rgb 'red' pt 7 ps 1 lt 1 lw 2 
set style line 2 lc rgb 'blue' pt 7 ps 1 lt 1 lw 2 
set style line 9 lc rgb 'green' pt 7 ps 1 lt 1 lw 2 
set style line 10 lc rgb 'dark-green' pt 7 ps 1 lt 1 lw 1
#set style fill transparent  solid 0.5 noborder
set style fill solid 0.5 noborder

# Keys settings
#set key bottom right

# Set title
set title "Title"

# Labels
set xlabel "x_label"
set ylabel "y_label"

# set logscale x 10

plot "file" u 1:2 t "data" w lp ls 1
