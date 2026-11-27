
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1630.49 | 0.260153 | 5638.99ms | 728486 | 320 | 3.93199e+08 | 426091 | 0.645786 | 1(Win) | true |
| Jsonifier (two-stage) | 1362.12 | 0.255699 | 6557.13ms | 728486 | 160 | 2.72138e+08 | 510042 | 0.0861565 | 2(Loss) | true |
| Glaze | 1037.81 | 0.532082 | 8676.12ms | 728486 | 80 | 1.01498e+09 | 669429 | 0.868995 | 3(Loss) | true |
| simdjson (ondemand) | 916.637 | 0.55564 | 9963.66ms | 728486 | 30 | 5.32054e+08 | 757921 | 0.301263 | 4(Loss) | true |
