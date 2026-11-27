
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1714.32 | 0.248733 | 9094.16ms | 461466 | 1280 | 5.21886e+08 | 256714 | 1.4001 | 1(Win) | true |
| Jsonifier (two-stage) | 1115.51 | 1.14064 | 5832.87ms | 461466 | 40 | 8.10013e+08 | 394519 | 2.0184 | 2(Loss) | true |
| Glaze | 938.687 | 0.43721 | 7171.33ms | 461466 | 80 | 3.36131e+08 | 468834 | 0.434821 | 3(Loss) | true |
| simdjson (ondemand) | 751.739 | 0.495454 | 8451.51ms | 461466 | 80 | 6.73041e+08 | 585427 | 0.70582 | 4(Loss) | true |
