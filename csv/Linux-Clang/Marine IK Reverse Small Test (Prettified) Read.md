
----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2380.58 | 0.0827891 | 1467.87ms | 18245 | 4890 | 179051 | 7309.06 | 0.335827 | 2.15874 | 8.60312 | 1.64483 | 0.00184493 | 0.000105999 | 7.1499e-05 | 1(Win) | true |
| Jsonifier | 2092.34 | 0.0860777 | 1571.09ms | 18245 | 4890 | 250560 | 8315.94 | 0.0264873 | 2.43558 | 9.19216 | 2.0912 | 0.00236264 | 2.35715e-05 | 1.07153e-05 | 2(Loss) | true |
| Glaze | 1879.19 | 0.13325 | 1667.91ms | 18245 | 80 | 12177.8 | 9259.17 | 0.0210646 | 2.70073 | 11.8384 | 2.39151 | 0.00335023 | 2.60345e-05 | 1.57577e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1835.56 | 0.0927245 | 1689.6ms | 18245 | 1280 | 98889.6 | 9479.29 | 0.0452344 | 2.76431 | 11.082 | 1.84812 | 0.00193495 | 8.26853e-05 | 4.78727e-05 | 4(Loss) | true |
