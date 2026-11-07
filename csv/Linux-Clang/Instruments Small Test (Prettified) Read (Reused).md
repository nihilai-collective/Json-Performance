
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3925.76 | 0.0639321 | 199.842ms | 7932 | 80 | 121.408 | 1926.9 | 0.247119 | 0.621765 | 1(Win) | true |
| Glaze | 2274.14 | 0.0702213 | 345.565ms | 7932 | 30 | 163.678 | 3326.33 | 0.160594 | 1.07972 | 2(Loss) | true |
| Jsonifier | 2230.42 | 0.236973 | 344.56ms | 7932 | 2560 | 165360 | 3391.53 | 0.228027 | 1.10161 | 3(Loss) | true |
| simdjson (ondemand) | 1156.26 | 0.195001 | 663.91ms | 7932 | 1280 | 208325 | 6542.28 | 0.261834 | 2.1322 | 4(Loss) | true |
