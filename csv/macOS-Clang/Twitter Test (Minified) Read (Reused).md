
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2647.3 | 0.283517 | 5094.42ms | 466906 | 1280 | 2.91085e+08 | 168200 | 0.524297 | 1(Win) | true |
| Jsonifier (two-stage) | 2152.43 | 0.164585 | 6455.64ms | 466906 | 80 | 9.27414e+06 | 206871 | 0.0849376 | 2(Loss) | true |
| Glaze | 1896.95 | 0.48788 | 7001.54ms | 466906 | 640 | 8.39371e+08 | 234733 | 0.680456 | 3(Loss) | true |
| simdjson (ondemand) | 873.571 | 0.267329 | 7067.63ms | 466906 | 30 | 5.57028e+07 | 509719 | 0.0950338 | 4(Loss) | true |
