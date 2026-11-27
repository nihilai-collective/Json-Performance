
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2141.41 | 0.190026 | 7087.54ms | 461466 | 80 | 1.2201e+07 | 205513 | 0.1198 | 1.15601 | 1(Win) | true |
| Jsonifier (two-stage) | 1638.11 | 0.0835169 | 8748.56ms | 461466 | 320 | 1.61098e+07 | 268656 | 0.282099 | 1.51119 | 2(Loss) | true |
| Glaze | 1365.72 | 0.286358 | 10014.5ms | 461466 | 30 | 2.55443e+07 | 322239 | 0.00226535 | 1.81266 | 3(Loss) | true |
| simdjson (ondemand) | 959.739 | 0.246382 | 6569.69ms | 461466 | 40 | 5.10566e+07 | 458550 | 0.409487 | 2.57948 | 4(Loss) | true |
