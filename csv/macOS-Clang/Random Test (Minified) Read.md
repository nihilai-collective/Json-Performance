
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1107.6 | 0.717941 | 5074.59ms | 461466 | 320 | 2.604e+09 | 397335 | 1.56654 | 1(Win) | true |
| Jsonifier (two-stage) | 916.202 | 1.002 | 6258.76ms | 461466 | 40 | 9.26606e+08 | 480340 | 2.00398 | 2(Loss) | true |
| Glaze | 860.35 | 0.154696 | 7223.42ms | 461466 | 30 | 1.87848e+07 | 511522 | 0.660553 | 3(Loss) | true |
| simdjson (ondemand) | 630.86 | 0.563661 | 8856.31ms | 461466 | 30 | 4.63842e+08 | 697600 | 0.00440577 | 4(Loss) | true |
