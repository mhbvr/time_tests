#set terminal png size $size noenhanced transparent interlace font 'Liberation Sans,9'
set terminal svg size 512,512 font 'Liberation Sans,9'
set output 'hist.svg'

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

set style fill transparent  solid 0.5 
#set style fill solid 0.5 noborder
#set boxwidth 0.95 relative


# Keys settings
#set key bottom right

# Set title
set title "Title"

# Labels
set xlabel "xlabel"
set ylabel "ylabel"

# set logscale x 10


plot "tmp/data" u 1:2 t "data" w boxes lc rgb 'green'
