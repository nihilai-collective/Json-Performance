
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4040.57 | 0.0473472 | 5093.03ms | 183677 | 640 | 269646 | 43352.3 | 0.43422 | 1.26161 | 5.87762 | 1.17775 | 0.00165741 | 9.46805e-06 | 6.20144e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3358.34 | 0.063109 | 5951.65ms | 183677 | 80 | 86682.7 | 52159.1 | 0.0149999 | 1.50535 | 7.01707 | 1.18184 | 0.00171259 | 2.10968e-06 | 6.12488e-07 | 2(Loss) | true |
| simdjson (reflection) | 2774.33 | 0.0802863 | 7053.43ms | 183677 | 80 | 205573 | 63138.8 | 0.178375 | 1.82196 | 8.11687 | 1.11465 | 0.00102061 | 7.82624e-06 | 6.46515e-06 | 3(Loss) | true |
| Glaze | 2589.23 | 0.0654682 | 7518.91ms | 183677 | 320 | 627740 | 67652.6 | 0.133045 | 1.96539 | 8.76916 | 1.71851 | 0.0033521 | 2.09097e-05 | 1.45806e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2414.9 | 0.0216331 | 8044.23ms | 183677 | 4890 | 1.20408e+06 | 72536.2 | 0.00529173 | 2.11167 | 9.2211 | 1.50345 | 0.00175075 | 2.63099e-05 | 1.87089e-05 | 5(Loss) | true |
