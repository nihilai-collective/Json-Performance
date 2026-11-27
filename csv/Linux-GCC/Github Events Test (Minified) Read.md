
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1883.69 | 0.114613 | 3467.97ms | 53331 | 640 | 612901 | 27000.4 | 0.18955 | 2.69134 | 8.43115 | 1.63265 | 0.0108544 | 6.5247e-05 | 3.50992e-05 | 1(Win) | true |
| simdjson (reflection) | 1656.01 | 0.0844994 | 3793.57ms | 53331 | 320 | 215521 | 30712.6 | 0.0983868 | 3.05472 | 10.8142 | 1.88687 | 0.00600917 | 6.0237e-05 | 3.39859e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1568.83 | 0.0451317 | 4021.37ms | 53331 | 4890 | 1.04684e+06 | 32419.3 | 0.133678 | 3.22044 | 11.3841 | 1.95372 | 0.00802802 | 6.92438e-05 | 4.43539e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1497.77 | 0.0312375 | 4164.78ms | 53331 | 2560 | 288048 | 33957.5 | 0.291933 | 3.38294 | 11.0617 | 2.03872 | 0.00219426 | 0.000106198 | 6.93268e-05 | 4(Loss) | true |
| Glaze | 1475.43 | 0.041897 | 4199.22ms | 53331 | 4890 | 1.02e+06 | 34471.7 | 0.0452251 | 3.42949 | 11.6038 | 2.26513 | 0.0194017 | 9.16451e-05 | 5.48874e-05 | 5(Loss) | true |
