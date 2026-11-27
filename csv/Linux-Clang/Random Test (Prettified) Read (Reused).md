
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2660.3 | 0.180901 | 8444.97ms | 728486 | 160 | 3.57097e+07 | 261151 | 0.105827 | 0.930526 | 1(Win) | true |
| Jsonifier (two-stage) | 2316.18 | 0.0760703 | 9495.55ms | 728486 | 1280 | 6.66405e+07 | 299950 | 0.0274374 | 1.06878 | 2(Loss) | true |
| Glaze | 1636.45 | 0.123091 | 6271.72ms | 728486 | 80 | 2.18466e+07 | 424540 | 0.121529 | 1.5128 | 3(Loss) | true |
| simdjson (ondemand) | 1428.76 | 0.12208 | 6965.16ms | 728486 | 640 | 2.25523e+08 | 486253 | 0.354349 | 1.73271 | 4(Loss) | true |
