
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1126.39 | 0.668294 | 5695.45ms | 4197495 | 40 | 2.25629e+10 | 3.55386e+06 | 3.58374 | 1(Win) | true |
| simdjson (ondemand) | 714.988 | 0.593017 | 8127.46ms | 4197495 | 80 | 8.81876e+10 | 5.59876e+06 | 3.04469 | 2(Loss) | true |
