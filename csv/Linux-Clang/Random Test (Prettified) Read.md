
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1698.91 | 0.169454 | 5295.29ms | 728486 | 30 | 1.44055e+07 | 408932 | 0.122747 | 1.45714 | 1(Win) | true |
| Jsonifier | 1410.47 | 0.125597 | 6326.64ms | 728486 | 640 | 2.44934e+08 | 492557 | 0.915149 | 1.75514 | 2(Loss) | true |
| Glaze | 1344.05 | 0.118078 | 6570.12ms | 728486 | 320 | 1.19207e+08 | 516900 | 1.46212 | 1.84191 | 3(Loss) | true |
| simdjson (ondemand) | 1179.88 | 0.136208 | 7470.42ms | 728486 | 80 | 5.14592e+07 | 588821 | 0.800713 | 2.09818 | 4(Loss) | true |
