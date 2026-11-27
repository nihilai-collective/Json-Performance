
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2358.95 | 0.487746 | 9114.13ms | 728486 | 80 | 1.65076e+08 | 294512 | 0.0149038 | 1.04942 | 1(Win) | true |
| simdjson (ondemand) | 2140.01 | 0.136963 | 9855.4ms | 728486 | 320 | 6.3266e+07 | 324643 | 0.0824591 | 1.1568 | 2(Loss) | true |
| Jsonifier (two-stage) | 2038.14 | 0.101991 | 5298.39ms | 728486 | 640 | 7.73531e+07 | 340868 | 1.23865 | 1.21461 | 3(Loss) | true |
| simdjson (reflection) | 2006.42 | 0.0941485 | 5109.66ms | 728486 | 640 | 6.80151e+07 | 346257 | 0.111805 | 1.23382 | 4(Loss) | true |
| Glaze | 1580.31 | 0.206836 | 6528.53ms | 728486 | 30 | 2.48048e+07 | 439623 | 0.103542 | 1.56655 | 5(Loss) | true |
