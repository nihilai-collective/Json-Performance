
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1259.18 | 0.924199 | 6030.23ms | 5373214 | 30 | 4.24372e+10 | 4.06956e+06 | 0.733651 | 1(Win) | true |
| Jsonifier (two-stage) | 1151.67 | 1.21627 | 6260.88ms | 5373214 | 40 | 1.17147e+11 | 4.44946e+06 | 1.62111 | 2(Loss) | true |
| Glaze | 1040.83 | 0.873269 | 7795.56ms | 5373214 | 40 | 7.39373e+10 | 4.92327e+06 | 1.03987 | 3(Loss) | true |
| simdjson (ondemand) | 962.374 | 0.99646 | 8238.58ms | 5373214 | 40 | 1.12606e+11 | 5.32464e+06 | 1.5462 | 4(Loss) | true |
