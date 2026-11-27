
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3422.69 | 0.229622 | 5166.29ms | 183677 | 160 | 2.20963e+06 | 51178.4 | 0.137123 | 1(Win) | true |
| simdjson (ondemand) | 2658.3 | 0.0757034 | 6665.49ms | 183677 | 2560 | 6.37051e+06 | 65894.9 | 0.107294 | 2(Loss) | true |
