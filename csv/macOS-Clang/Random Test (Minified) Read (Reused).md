
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1536.95 | 0.949626 | 9627.48ms | 461466 | 80 | 5.91502e+08 | 286339 | 0.793823 | 1(Win) | true |
| Jsonifier (two-stage) | 1176.16 | 0.502983 | 6268.98ms | 461466 | 320 | 1.13345e+09 | 374172 | 3.8643 | 2(Loss) | true |
| Glaze | 870.635 | 0.713498 | 7276.41ms | 461466 | 160 | 2.08119e+09 | 505480 | 0.228133 | 3(Loss) | true |
| simdjson (ondemand) | 669.522 | 0.663117 | 9588.7ms | 461466 | 160 | 3.03983e+09 | 657317 | 1.24888 | 4(Loss) | true |
