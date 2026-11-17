
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3748.22 | 0.22281 | 4820.4ms | 183677 | 160 | 1.73479e+06 | 46733.6 | 1.25546 | 0.660124 | 1(Win) | true |
| Jsonifier | 2256.37 | 0.111294 | 8027.62ms | 183677 | 2560 | 1.91104e+07 | 77632.6 | 0.0293944 | 1.09686 | 2(Loss) | true |
| Glaze | 2235.11 | 0.205535 | 8237.7ms | 183677 | 160 | 4.15149e+06 | 78371.1 | 0.0331725 | 1.10733 | 3(Loss) | true |
| simdjson (ondemand) | 1138.9 | 0.155398 | 7960.7ms | 183677 | 1280 | 7.31214e+07 | 153805 | 0.322131 | 2.17345 | 4(Loss) | true |
