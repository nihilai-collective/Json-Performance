
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1273.63 | 0.123347 | 5921.52ms | 4506446 | 30 | 5.19704e+08 | 3.37434e+06 | 0.177781 | 1.94385 | 1(Win) | true |
| simdjson (ondemand) | 1039.45 | 0.146163 | 7038.96ms | 4506446 | 80 | 2.92162e+09 | 4.13457e+06 | 0.213033 | 2.38179 | 2(Loss) | true |
