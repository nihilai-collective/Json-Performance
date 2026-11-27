
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2053.52 | 0.22455 | 5422.21ms | 728486 | 320 | 1.84681e+08 | 338316 | 0.701107 | 1(Win) | true |
| Jsonifier (two-stage) | 1689.02 | 0.0985939 | 6319.81ms | 728486 | 640 | 1.05257e+08 | 411325 | 0.0454835 | 2(Loss) | true |
| Glaze | 1329.91 | 0.164165 | 7901.91ms | 728486 | 320 | 2.35349e+08 | 522396 | 0.961892 | 3(Loss) | true |
| simdjson (ondemand) | 899.491 | 0.889088 | 5213.04ms | 728486 | 320 | 1.509e+10 | 772368 | 0.938784 | 4(Loss) | true |
