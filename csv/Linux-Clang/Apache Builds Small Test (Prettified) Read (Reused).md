
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3603.21 | 0.084778 | 98.2962ms | 3370 | 80 | 45.7443 | 891.95 | 0.0897716 | 0.667125 | 1(Win) | true |
| Glaze | 2732.73 | 0.0418755 | 127.016ms | 3370 | 160 | 38.8066 | 1176.07 | 0.0356186 | 0.885888 | 2(Loss) | true |
| Jsonifier | 2631.26 | 0.0287505 | 132.492ms | 3370 | 320 | 39.4614 | 1221.42 | 0.0829638 | 0.920691 | 3(Loss) | true |
| simdjson (ondemand) | 2189.41 | 0.0675822 | 159.024ms | 3370 | 320 | 314.934 | 1467.92 | 0.0749922 | 1.11037 | 4(Loss) | true |
