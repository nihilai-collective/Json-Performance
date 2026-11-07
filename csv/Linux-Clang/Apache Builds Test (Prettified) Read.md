
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1950.19 | 0.174595 | 6177ms | 124597 | 320 | 3.6214e+06 | 60930.1 | 0.0780306 | 1.26895 | 1(Win) | true |
| Jsonifier | 1715.26 | 0.154194 | 6807.32ms | 124597 | 640 | 7.30244e+06 | 69275.1 | 0.405924 | 1.44282 | 2(Loss) | true |
| Glaze | 1617.71 | 0.0886739 | 7232.79ms | 124597 | 1280 | 5.43023e+06 | 73452.8 | 0.0316419 | 1.52986 | 3(Loss) | true |
| simdjson (ondemand) | 1417.43 | 0.0902328 | 8423.32ms | 124597 | 1280 | 7.32403e+06 | 83831.2 | 0.163187 | 1.74612 | 4(Loss) | true |
