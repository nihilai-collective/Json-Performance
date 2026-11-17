
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1589.39 | 0.0965876 | 7867.13ms | 4197495 | 160 | 9.46854e+08 | 2.5186e+06 | 1.69123 | 1.55769 | 1(Win) | true |
| simdjson (ondemand) | 1295.41 | 0.302111 | 9788.82ms | 4197495 | 30 | 2.61468e+09 | 3.09016e+06 | 1.29842 | 1.91118 | 2(Loss) | true |
