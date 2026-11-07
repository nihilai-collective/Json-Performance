
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1593.42 | 0.435935 | 6697.78ms | 108313 | 80 | 6.38905e+06 | 64826.2 | 0.428155 | 1.55309 | 1(Win) | true |
| Jsonifier (two-stage) | 1183.95 | 0.0929761 | 8824.98ms | 108313 | 2560 | 1.68452e+07 | 87246.1 | 0.0320676 | 2.09049 | 2(Loss) | true |
| Glaze | 957.48 | 0.796773 | 5646.5ms | 108313 | 160 | 1.1822e+08 | 107882 | 0.657787 | 2.58501 | 3(Loss) | true |
| simdjson (ondemand) | 780.224 | 0.33572 | 6902.23ms | 108313 | 160 | 3.16079e+07 | 132392 | 0.0344502 | 3.1725 | 4(Loss) | true |
