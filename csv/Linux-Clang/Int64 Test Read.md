
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2872.51 | 0.0421072 | 131.205ms | 3862 | 80 | 23.3188 | 1282.19 | 0.041903 | 0.843371 | 1(Win) | true |
| Glaze | 1430.89 | 0.0392508 | 262.353ms | 3862 | 80 | 81.6581 | 2573.99 | 0.00534219 | 1.71224 | 2(Loss) | true |
| Jsonifier (two-stage) | 927.263 | 0.0369486 | 401.96ms | 3862 | 40 | 86.1538 | 3972 | 0.0176265 | 2.6543 | 3(Loss) | true |
| simdjson (ondemand) | 687.513 | 0.155701 | 539.078ms | 3862 | 2560 | 178110 | 5357.12 | 0.140096 | 3.58384 | 4(Loss) | true |
