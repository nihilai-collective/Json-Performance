
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1802.76 | 0.175039 | 9817.94ms | 728486 | 40 | 1.82011e+07 | 385376 | 0.0275695 | 1.37317 | 1(Win) | true |
| Jsonifier | 1445.88 | 0.412441 | 5967.46ms | 728486 | 40 | 1.57095e+08 | 480495 | 0.333315 | 1.71218 | 2(Loss) | true |
| Glaze | 1410.36 | 0.24656 | 6294.08ms | 728486 | 30 | 4.42536e+07 | 492596 | 0.498877 | 1.7553 | 3(Loss) | true |
| simdjson (ondemand) | 1254.09 | 0.132068 | 7053.69ms | 728486 | 80 | 4.28223e+07 | 553980 | 0.0290788 | 1.97405 | 4(Loss) | true |
