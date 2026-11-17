
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2260.2 | 0.0487656 | 9832.59ms | 728486 | 1280 | 2.87598e+07 | 307380 | 0.058487 | 2.22151 | 9.72359 | 1.66029 | 0.0138736 | 0.0329691 | 9.25046e-05 | 1(Win) | true |
| Glaze | 1958.02 | 0.105479 | 5509.5ms | 728486 | 320 | 4.48219e+07 | 354816 | 0.0929301 | 2.57183 | 12.312 | 2.38192 | 0.00899919 | 0.00983774 | 4.01732e-05 | 2(Loss) | true |
| Jsonifier | 1790.64 | 0.0726214 | 5894.02ms | 728486 | 640 | 5.08084e+07 | 387984 | 0.111646 | 2.81632 | 11.1708 | 2.24471 | 0.0113823 | 0.0087301 | 5.40762e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1559.04 | 0.103774 | 6564.95ms | 728486 | 640 | 1.36863e+08 | 445621 | 0.0984548 | 3.19583 | 13.9356 | 2.27086 | 0.00265535 | 0.0338856 | 6.3342e-05 | 4(Loss) | true |
