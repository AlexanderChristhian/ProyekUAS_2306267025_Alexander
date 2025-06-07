set title 'Capacitor Charging Curve - Case 5: Low R, High C (6V, 330Ω, 1000µF)'
set xlabel 'Time (s)'
set ylabel 'Voltage (V)'
set grid
plot 'capacitor_data_case5.txt' using 1:2 with lines title 'Numerical Solution', 6.000000*(1-exp(-x/(330.000000*0.001000))) title 'Analytical Solution'
