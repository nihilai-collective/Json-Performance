
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1530.73 | 0.92701 | 5136.8ms | 631514 | 160 | 2.12842e+09 | 393446 | 0.904192 | 1.61717 | 1(Win) | true |
| simdjson (ondemand) | 1398.71 | 0.404923 | 5535.96ms | 631514 | 320 | 9.72758e+08 | 430582 | 0.540155 | 1.76987 | 2(Loss) | true |
| Glaze | 1358.86 | 0.535266 | 5941.7ms | 631514 | 30 | 1.68842e+08 | 443210 | 0.676919 | 1.82182 | 3(Loss) | true |
| Jsonifier | 1328.15 | 0.456809 | 5935.79ms | 631514 | 640 | 2.74615e+09 | 453458 | 0.133252 | 1.86389 | 4(Loss) | true |
