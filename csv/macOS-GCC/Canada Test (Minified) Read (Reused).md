
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 921.858 | 0.211465 | 9196.61ms | 2251027 | 160 | 3.88e+09 | 2.32872e+06 | 0.457685 | 1(Win) | true |
| Glaze | 771.429 | 0.0570329 | 5134.19ms | 2251027 | 80 | 2.01517e+08 | 2.78282e+06 | 0.0736551 | 2(Loss) | true |
| simdjson (reflection) | 760.475 | 0.0963832 | 5128.61ms | 2251027 | 30 | 2.22083e+08 | 2.8229e+06 | 0.00423223 | 3(Loss) | true |
| simdjson (ondemand) | 685.165 | 0.0657268 | 5542.83ms | 2251027 | 80 | 3.39271e+08 | 3.13318e+06 | 0.0950736 | 4(Loss) | true |
| Jsonifier (two-stage) | 650.376 | 0.400405 | 5529.88ms | 2251027 | 30 | 5.24026e+09 | 3.30078e+06 | 3.16411 | 5(Loss) | true |
