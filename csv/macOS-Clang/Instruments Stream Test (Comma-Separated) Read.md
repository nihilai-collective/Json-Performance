
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1180.15 | 0.29343 | 5155.57ms | 4197495 | 80 | 7.92515e+09 | 3.39198e+06 | 0.305259 | 1(Win) | true |
| simdjson (ondemand) | 849.897 | 0.298259 | 7198.77ms | 4197495 | 30 | 5.92048e+09 | 4.71003e+06 | 0.0369603 | 2(Loss) | true |
