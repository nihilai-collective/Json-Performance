
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1673.37 | 0.354431 | 195.353ms | 3370 | 2560 | 118625 | 1920.6 | 0.290728 | 1(Win) | true |
| Jsonifier | 1523.48 | 0.247259 | 214.871ms | 3370 | 4890 | 133045 | 2109.57 | 0.0600315 | 2(Loss) | true |
| Glaze | 1408.61 | 1.58674 | 250.343ms | 3370 | 160 | 209705 | 2281.6 | 0.140056 | 3(Loss) | true |
| simdjson (reflection) | 1284.99 | 0.431107 | 248.939ms | 3370 | 2560 | 297626 | 2501.1 | 1.6129 | 4(Loss) | true |
| simdjson (ondemand) | 979.364 | 0.320535 | 336.998ms | 3370 | 2560 | 283244 | 3281.6 | 0.635863 | 5(Loss) | true |
