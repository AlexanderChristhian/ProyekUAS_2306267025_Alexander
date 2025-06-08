<div align="center">
    <h1>
        Simulasi Pengisian Kapasitor Menggunakan Metode Euler
    </h1>
</div>

## Deskripsi Proyek

<div align="justify">
Proyek ini mengimplementasikan simulasi pengisian kapasitor menggunakan metode Euler untuk menyelesaikan persamaan diferensial biasa (ODE). Program dikembangkan dalam bahasa C dan menganalisis perilaku pengisian kapasitor dengan berbagai parameter rangkaian, membandingkan solusi numerik dengan solusi analitik, dan memvisualisasikan hasilnya menggunakan GNUplot.

Program ini mensimulasikan lima kasus berbeda untuk menunjukkan pengaruh variasi parameter rangkaian terhadap karakteristik pengisian kapasitor, termasuk analisis error dan perbandingan dengan solusi analitik.
</div>

## Instalasi dan Kompilasi

<details open>
    <summary> Prerequisites </summary>
    <li> 
    GCC (compiler C)
    </li>
    <li>
    Gnuplot (untuk visualisasi hasil)
    </li>
    <li>
    Git (untuk clone repository)
    </li>
</details>

<br>

<details open>
    <summary> Kompilasi Program </summary>

```console
# Kompilasi program utama
gcc src/main.c -o src/main -lm
```
</details>

<details open>
    <summary> Menjalankan Program </summary>

```console
# Menjalankan program
cd src
./main
```
</details>

## Model Matematika

### Persamaan Diferensial Pengisian Kapasitor

$$
\frac{dV}{dt} = \frac{V_{source} - V}{RC}
$$

| Simbol | Keterangan |
|--------|------------|
| V      | Tegangan kapasitor pada waktu t |
| V_source | Tegangan sumber |
| R      | Resistansi |
| C      | Kapasitansi |
| t      | Waktu |

### Solusi Analitik

$$
V(t) = V_{source}(1 - e^{-t/RC})
$$

### Metode Euler

$$
V_{n+1} = V_n + \Delta t \cdot \frac{V_{source} - V_n}{RC}
$$

| Simbol | Keterangan |
|--------|------------|
| V_n    | Tegangan pada langkah ke-n |
| Δt     | Ukuran langkah waktu |
| RC     | Konstanta waktu rangkaian |

## Kasus Uji

Program menganalisis lima kasus dengan parameter berbeda:

<table>
<tr>
    <th>Kasus</th>
    <th>V_source (V)</th>
    <th>R (Ω)</th>
    <th>C (µF)</th>
    <th>τ = RC (s)</th>
</tr>
<tr>
    <td>Standard</td>
    <td>5.0</td>
    <td>1000</td>
    <td>100</td>
    <td>0.1</td>
</tr>
<tr>
    <td>High Voltage</td>
    <td>12.0</td>
    <td>2200</td>
    <td>220</td>
    <td>0.484</td>
</tr>
<tr>
    <td>Low Voltage</td>
    <td>3.3</td>
    <td>470</td>
    <td>470</td>
    <td>0.2209</td>
</tr>
<tr>
    <td>High R, Low C</td>
    <td>9.0</td>
    <td>4700</td>
    <td>33</td>
    <td>0.1551</td>
</tr>
<tr>
    <td>Low R, High C</td>
    <td>6.0</td>
    <td>330</td>
    <td>1000</td>
    <td>0.33</td>
</tr>
</table>

## Hasil Simulasi

### Error Analysis

Program menghasilkan error relatif yang rendah untuk semua kasus:

| Kasus | Error Max (%) | Error Rata-rata (%) |
|-------|---------------|-------------------|
| Standard | 5.0833 | 0.8221 |
| High Voltage | 1.0366 | 0.6193 |
| Low Voltage | 2.2805 | 0.7939 |
| High R, Low C | 3.2584 | 0.8170 |
| Low R, High C | 1.5228 | 0.7253 |

### Waktu Eksekusi

Program menunjukkan performa komputasi yang konsisten:

| Kasus | Waktu Eksekusi (detik) |
|-------|----------------------|
| Standard | 0.009 |
| High Voltage | 0.009 |
| Low Voltage | 0.009 |
| High R, Low C | 0.009 |
| Low R, High C | 0.008 |

## Output Program

Program menghasilkan:
1. File data untuk setiap kasus (capacitor_data_case[1-5].txt)
2. Script GNUplot untuk visualisasi (plot_capacitor_case[1-5].gnu)
3. Grafik perbandingan solusi numerik dan analitik
4. Analisis error dan waktu eksekusi

## Visualisasi

Program menghasilkan grafik untuk setiap kasus yang menunjukkan:
- Solusi numerik (metode Euler)
- Solusi analitik untuk perbandingan
- Kurva pengisian karakteristik

## Pengembang

| Nama | NPM |
|------|-----|
| Alexander Christhian | 2306267025 |

## Link Youtube
https://youtu.be/z8P75XzYrC8
