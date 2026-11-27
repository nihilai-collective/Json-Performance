
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2204.51 | 0.235289 | 5296.94ms | 728486 | 30 | 1.64947e+07 | 315145 | 0.280815 | 1(Win) | true |
| Jsonifier (two-stage) | 1873.6 | 0.12335 | 6047.08ms | 728486 | 640 | 1.3389e+08 | 370804 | 0.30178 | 2(Loss) | true |
| Glaze | 1462.09 | 0.143156 | 7491.11ms | 728486 | 40 | 1.85087e+07 | 475168 | 0.235152 | 3(Loss) | true |
| simdjson (reflection) | 1453.7 | 0.173947 | 7369.82ms | 728486 | 30 | 2.07324e+07 | 477909 | 0.019645 | 4(Loss) | true |
| simdjson (ondemand) | 1293.14 | 0.103122 | 8182.49ms | 728486 | 640 | 1.9644e+08 | 537247 | 0.0537266 | 5(Loss) | true |
