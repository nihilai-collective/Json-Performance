
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2404.62 | 0.765989 | 6501.65ms | 461466 | 320 | 6.28901e+08 | 183018 | 0.319222 | 2.10287 | 10.7456 | 1.88237 | 0.00663722 | 0.00471952 | 7.59197e-05 | 1(Win) | true |
| simdjson (reflection) | 1555.52 | 0.22442 | 9070.21ms | 461466 | 640 | 2.58005e+08 | 282920 | 0.0423019 | 3.23178 | 14.8656 | 2.35967 | 0.00373159 | 0.0220451 | 2.24387e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1525.08 | 0.153839 | 9329.67ms | 461466 | 1280 | 2.52253e+08 | 288568 | 0.276977 | 3.3208 | 15.7331 | 2.51029 | 0.0182999 | 0.0243213 | 2.36305e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1328.43 | 0.201926 | 5120.46ms | 461466 | 640 | 2.86396e+08 | 331284 | 0.0629845 | 3.79203 | 16.1988 | 2.66445 | 0.0036602 | 0.0270395 | 2.27773e-05 | 4(Loss) | true |
| Glaze | 1311 | 0.409895 | 5219.16ms | 461466 | 640 | 1.21171e+09 | 335688 | 0.124477 | 3.85652 | 16.3071 | 3.07786 | 0.0215329 | 0.0101633 | 5.01628e-05 | 5(Loss) | true |
