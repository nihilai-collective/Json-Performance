
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1612.01 | 0.0563716 | 7168.21ms | 461466 | 1280 | 3.03164e+07 | 273007 | 0.019678 | 3.13276 | 14.7673 | 2.94341 | 0.00683674 | 0.0331127 | 3.12946e-05 | 1(Win) | true |
| Glaze | 1185.31 | 0.0807921 | 9680.51ms | 461466 | 640 | 5.75886e+07 | 371287 | 0.00120062 | 4.26167 | 19.1483 | 3.78675 | 0.0127289 | 0.0276589 | 6.76614e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1132.78 | 0.0905667 | 5033.4ms | 461466 | 320 | 3.96164e+07 | 388503 | 0.0925448 | 4.44941 | 19.8289 | 3.51211 | 0.0175387 | 0.0718531 | 4.96041e-05 | 3(Loss) | true |
| simdjson (ondemand) | 818.267 | 0.0881054 | 6984.64ms | 461466 | 640 | 1.43706e+08 | 537830 | 0.0759674 | 6.1454 | 25.5576 | 4.45151 | 0.0106381 | 0.0831124 | 0.000163639 | 4(Loss) | true |
