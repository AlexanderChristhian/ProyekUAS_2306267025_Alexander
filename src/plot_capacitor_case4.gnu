set title 'Capacitor Charging Curve - Case 4: High R, Low C (9V, 4.7kΩ, 33µF)'
set xlabel 'Time (s)'
set ylabel 'Voltage (V)'
set grid
plot 'capacitor_data_case4.txt' using 1:2 with lines title 'Numerical Solution', 9.000000*(1-exp(-x/(4700.000000*0.000033))) title 'Analytical Solution'
