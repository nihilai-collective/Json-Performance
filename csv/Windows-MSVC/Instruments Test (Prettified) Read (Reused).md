
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2054.18 | 0.22306 | 9011.53ms | 183677 | 320 | 1.15778e+07 | 85274.1 | 0.625784 | 1.20483 | 1(Win) | true |
| Jsonifier | 1832.23 | 0.144617 | 5128.15ms | 183677 | 640 | 1.22339e+07 | 95603.6 | 0.320211 | 1.35085 | 2(Loss) | true |
| Glaze | 1561.65 | 0.269121 | 6044ms | 183677 | 160 | 1.458e+07 | 112169 | 0.0723831 | 1.58504 | 3(Loss) | true |
| simdjson (ondemand) | 1235.43 | 0.249342 | 7606.25ms | 183677 | 160 | 1.99979e+07 | 141787 | 0.162921 | 2.00357 | 4(Loss) | true |
