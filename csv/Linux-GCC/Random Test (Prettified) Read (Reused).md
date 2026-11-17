
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2263.44 | 0.193569 | 9275.51ms | 728486 | 320 | 1.1296e+08 | 306939 | 0.00472282 | 1.09372 | 1(Win) | true |
| simdjson (ondemand) | 2135.34 | 0.26516 | 9725.61ms | 728486 | 40 | 2.97705e+07 | 325353 | 0.305497 | 1.15933 | 2(Loss) | true |
| Jsonifier (two-stage) | 2100.78 | 0.16852 | 5135.5ms | 728486 | 40 | 1.24235e+07 | 330705 | 1.15035 | 1.17841 | 3(Loss) | true |
| Jsonifier | 1885.27 | 0.194062 | 5605.46ms | 728486 | 30 | 1.53425e+07 | 368508 | 0.032517 | 1.31315 | 4(Loss) | true |
| Glaze | 1674.77 | 0.0954135 | 6305.12ms | 728486 | 80 | 1.25327e+07 | 414827 | 0.138949 | 1.47819 | 5(Loss) | true |
