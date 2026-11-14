
----
### Random Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2044.97 | 0.3942 | 7993.65ms | 676745 | 80 | 1.23822e+08 | 315600 | 2.31472 | 1(Win) | true |
| simdjson (ondemand) | 1496.19 | 0.229806 | 5705.52ms | 676745 | 30 | 2.94796e+07 | 431358 | 0.25183 | 2(Loss) | true |
