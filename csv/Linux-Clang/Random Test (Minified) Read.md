
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1290.81 | 0.108805 | 8800.6ms | 461466 | 320 | 4.40357e+07 | 340939 | 0.0221371 | 1.91775 | 1(Win) | true |
| Glaze | 1104.72 | 0.0866902 | 5068.37ms | 461466 | 320 | 3.81647e+07 | 398369 | 0.288477 | 2.2409 | 2(Loss) | true |
| Jsonifier (two-stage) | 1068.42 | 0.385141 | 5127.07ms | 461466 | 40 | 1.00669e+08 | 411907 | 0.46364 | 2.31707 | 3(Loss) | true |
| simdjson (ondemand) | 779.072 | 0.159282 | 7198.48ms | 461466 | 320 | 2.59063e+08 | 564888 | 0.132383 | 3.17766 | 4(Loss) | true |
