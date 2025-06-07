set title 'Capacitor Charging Curve - Case 3: Low Voltage (3.3V, 470Ω, 470µF)'
set xlabel 'Time (s)'
set ylabel 'Voltage (V)'
set grid
plot 'capacitor_data_case3.txt' using 1:2 with lines title 'Numerical Solution', 3.300000*(1-exp(-x/(470.000000*0.000470))) title 'Analytical Solution'
