
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2563.09 | 0.243942 | 8230.47ms | 631514 | 40 | 1.31423e+07 | 234974 | 0.445457 | 1(Win) | true |
| Jsonifier | 2155.61 | 0.818788 | 7904.27ms | 631514 | 320 | 1.67463e+09 | 279392 | 0.0373652 | 2(Loss) | true |
| Glaze | 1870.53 | 0.527353 | 9007.79ms | 631514 | 1280 | 3.69021e+09 | 321973 | 3.9464 | 3(Loss) | true |
| simdjson (ondemand) | 892.044 | 1.91502 | 8324.59ms | 631514 | 80 | 1.3373e+10 | 675145 | 1.50882 | 4(Loss) | true |
