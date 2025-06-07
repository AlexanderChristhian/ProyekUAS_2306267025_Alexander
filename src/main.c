#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define V_INITIAL 0.0    // Tegangan awal
#define T_FINAL 1.0      // Waktu akhir (s)
#define N 100            // Jumlah langkah
#define DT (T_FINAL/N)   // Ukuran langkah waktu
#define CASES 5          // Jumlah kasus uji

// Struktur untuk menyimpan parameter rangkaian
typedef struct {
    double V_source;
    double R;
    double C;
    char* description;
} CircuitParams;

// Fungsi untuk menghitung dV/dt
double dVdt(double V, CircuitParams params) {
    return (params.V_source - V)/(params.R * params.C);
}

// Inisialisasi kasus uji
CircuitParams initTestCases() {
    static CircuitParams cases[CASES] = {
        {5.0, 1000.0, 100e-6, "Case 1: Standard (5V, 1kΩ, 100µF)"},
        {12.0, 2200.0, 220e-6, "Case 2: High Voltage (12V, 2.2kΩ, 220µF)"},
        {3.3, 470.0, 470e-6, "Case 3: Low Voltage (3.3V, 470Ω, 470µF)"},
        {9.0, 4700.0, 33e-6, "Case 4: High R, Low C (9V, 4.7kΩ, 33µF)"},
        {6.0, 330.0, 1000e-6, "Case 5: Low R, High C (6V, 330Ω, 1000µF)"}
    };
    return cases[0]; // Mengembalikan kasus pertama untuk memenuhi kompiler
}

int main() {
    // Dapatkan kasus uji
    CircuitParams cases[CASES] = {
        {5.0, 1000.0, 100e-6, "Case 1: Standard (5V, 1kΩ, 100µF)"},
        {12.0, 2200.0, 220e-6, "Case 2: High Voltage (12V, 2.2kΩ, 220µF)"},
        {3.3, 470.0, 470e-6, "Case 3: Low Voltage (3.3V, 470Ω, 470µF)"},
        {9.0, 4700.0, 33e-6, "Case 4: High R, Low C (9V, 4.7kΩ, 33µF)"},
        {6.0, 330.0, 1000e-6, "Case 5: Low R, High C (6V, 330Ω, 1000µF)"}
    };
    
    // Array untuk waktu dan tegangan (untuk setiap kasus)
    double t[CASES][N+1], V[CASES][N+1];
    
    // Proses setiap kasus uji
    for (int c = 0; c < CASES; c++) {
        // Mulai perhitungan waktu untuk kasus ini
        clock_t start_case = clock();
        
        // Buat nama file untuk kasus ini
        char filename[50];
        sprintf(filename, "capacitor_data_case%d.txt", c+1);
        
        // Buka file untuk kasus ini
        FILE *fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Error opening file %s!\n", filename);
            return 1;
        }
        
        // Cetak deskripsi kasus dan parameter rangkaian
        printf("\n%s\n", cases[c].description);
        printf("Circuit Parameters:\n");
        printf("Source Voltage (V_s) = %.2f V\n", cases[c].V_source);
        printf("Resistance (R) = %.2f Ω\n", cases[c].R);
        printf("Capacitance (C) = %.2e F\n", cases[c].C);
        printf("Time Constant (τ = RC) = %.4f s\n\n", cases[c].R * cases[c].C);
        
        fprintf(fp, "\n%s\n", cases[c].description);
        fprintf(fp, "Circuit Parameters:\n");
        fprintf(fp, "Source Voltage (V_s) = %.2f V\n", cases[c].V_source);
        fprintf(fp, "Resistance (R) = %.2f Ω\n", cases[c].R);
        fprintf(fp, "Capacitance (C) = %.2e F\n", cases[c].C);
        fprintf(fp, "Time Constant (τ = RC) = %.4f s\n\n", cases[c].R * cases[c].C);
        
        // Tulis header untuk kasus ini dengan pemisah yang lebih jelas
        // Persamaan analitik
        fprintf(fp, "\nAnalytical Solution:\n");
        fprintf(fp, "V(t) = %.2f * (1 - e^(-t/%.4f))\n", cases[c].V_source, cases[c].R * cases[c].C);
        fprintf(fp, "where τ = RC = %.4f seconds\n\n", cases[c].R * cases[c].C);
        
        // Tabel hasil perhitungan
        fprintf(fp, "Time(s)          V_num(V)        V_analytic(V)      dV/dt(V/s)        Error(%%)\n");
        fprintf(fp, "--------------------------------------------------------------------------------\n");
        printf("Time(s)\tV_num(V)\tV_analytic(V)\tdV/dt(V/s)\tError(%%)\n");
        
        // Kondisi awal
        t[c][0] = 0.0;
        V[c][0] = V_INITIAL;
        
        // Iterasi metode Euler
        for(int i = 0; i < N; i++) {
            // Hitung nilai berikutnya menggunakan metode Euler
            V[c][i+1] = V[c][i] + DT * dVdt(V[c][i], cases[c]);
            t[c][i+1] = t[c][i] + DT;
            
            // Hitung solusi analitik untuk perbandingan error
            double V_analytical = cases[c].V_source * (1 - exp(-t[c][i+1]/(cases[c].R * cases[c].C)));
            double error = fabs((V[c][i+1] - V_analytical)/V_analytical) * 100;
            
            // Tulis hasil ke file dan konsol
            fprintf(fp, "%-16.4f%-16.4f%-16.4f%-16.4f%-16.4f\n", 
                t[c][i+1], V[c][i+1], V_analytical, dVdt(V[c][i+1], cases[c]), error);
            printf("%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", 
                t[c][i+1], V[c][i+1], V_analytical, dVdt(V[c][i+1], cases[c]), error);
        }
        
        // Akhiri perhitungan waktu untuk kasus ini
        clock_t end_case = clock();
        double case_time = ((double) (end_case - start_case)) / CLOCKS_PER_SEC;
        
        // Tambahkan ringkasan statistik
        double max_error = 0.0;
        double avg_error = 0.0;
        for(int i = 0; i < N; i++) {
            double V_analytical = cases[c].V_source * (1 - exp(-t[c][i+1]/(cases[c].R * cases[c].C)));
            double error = fabs((V[c][i+1] - V_analytical)/V_analytical) * 100;
            max_error = fmax(max_error, error);
            avg_error += error;
        }
        avg_error /= N;
        
        fprintf(fp, "\nSimulation Summary:\n");
        fprintf(fp, "--------------------------------------------------------------------------------\n");
        fprintf(fp, "Maximum Error: %.4f%%\n", max_error);
        fprintf(fp, "Average Error: %.4f%%\n", avg_error);
        fprintf(fp, "Case execution time: %.6f seconds\n", case_time);
        
        // Cetak waktu eksekusi untuk kasus ini
        printf("\nCase %d execution time: %.6f seconds\n", c+1, case_time);
        
        // Tutup file data untuk kasus ini
        fclose(fp);
        
        // Buat script GNUplot untuk kasus ini
        char plotname[50];
        sprintf(plotname, "plot_capacitor_case%d.gnu", c+1);
        FILE *gnuplot = fopen(plotname, "w");
        
        fprintf(gnuplot, "set title 'Capacitor Charging Curve - %s'\n", cases[c].description);
        fprintf(gnuplot, "set xlabel 'Time (s)'\n");
        fprintf(gnuplot, "set ylabel 'Voltage (V)'\n");
        fprintf(gnuplot, "set grid\n");
        
        // Plot solusi numerik dan analitik
        fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Numerical Solution', ", filename);
        fprintf(gnuplot, "%f*(1-exp(-x/(%f*%f))) title 'Analytical Solution'\n",
            cases[c].V_source, cases[c].R, cases[c].C);
        fclose(gnuplot);
        
        // Jalankan script GNUplot untuk kasus ini
        printf("\nGenerating plot for case %d...\n", c+1);
        char cmd[100];
        sprintf(cmd, "gnuplot -persist %s", plotname);
        system(cmd);
        
    }
    
    return 0;
}
