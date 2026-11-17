
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2168.42 | 0.0869988 | 184.041ms | 3808 | 160 | 339.667 | 1674.76 | 0.0500321 | 1(Win) | true |
| Glaze | 2005.35 | 0.178416 | 196.133ms | 3808 | 80 | 835.162 | 1810.95 | 0.0855172 | 2(Loss) | true |
| Jsonifier | 1806.85 | 4.64818 | 180.526ms | 3808 | 160 | 1.39648e+06 | 2009.9 | 0.618078 | 3(Loss) | true |
| simdjson (ondemand) | 1058.15 | 0.179579 | 378.746ms | 3808 | 30 | 1139.55 | 3432.03 | 0.0388346 | 4(Loss) | true |
