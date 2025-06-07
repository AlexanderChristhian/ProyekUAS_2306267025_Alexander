set title 'Capacitor Charging Curve - Case 2: High Voltage (12V, 2.2kΩ, 220µF)'
set xlabel 'Time (s)'
set ylabel 'Voltage (V)'
set grid
plot 'capacitor_data_case2.txt' using 1:2 with lines title 'Numerical Solution', 12.000000*(1-exp(-x/(2200.000000*0.000220))) title 'Analytical Solution'
