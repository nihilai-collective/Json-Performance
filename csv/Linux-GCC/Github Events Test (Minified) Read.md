
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1847.53 | 0.110051 | 2748.74ms | 53331 | 4890 | 4.48826e+06 | 27528.9 | 0.511161 | 1.33861 | 1(Win) | true |
| simdjson (reflection) | 1652.55 | 0.0839929 | 3092.84ms | 53331 | 4890 | 3.2677e+06 | 30776.9 | 0.111101 | 1.49679 | 2(Loss) | true |
| Jsonifier (two-stage) | 1539.96 | 0.35476 | 3358.77ms | 53331 | 320 | 4.39301e+06 | 33027.1 | 0.531222 | 1.60634 | 3(Loss) | true |
| Glaze | 1363.19 | 0.106616 | 3725.61ms | 53331 | 2560 | 4.05069e+06 | 37309.7 | 0.199611 | 1.81473 | 4(Loss) | true |
| simdjson (ondemand) | 1176.36 | 0.654934 | 4109.42ms | 53331 | 80 | 6.41457e+06 | 43235.6 | 0.364138 | 2.10329 | 5(Loss) | true |
