set title 'Capacitor Charging Curve - Case 1: Standard (5V, 1kΩ, 100µF)'
set xlabel 'Time (s)'
set ylabel 'Voltage (V)'
set grid
plot 'capacitor_data_case1.txt' using 1:2 with lines title 'Numerical Solution', 5.000000*(1-exp(-x/(1000.000000*0.000100))) title 'Analytical Solution'
