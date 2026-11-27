
----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3343.34 | 0.0591412 | 3120.29ms | 108313 | 40 | 13354.9 | 30895.8 | 0.0406368 | 1(Win) | true |
| simdjson (ondemand) | 2707.8 | 0.0757755 | 3831.22ms | 108313 | 4890 | 4.08598e+06 | 38147.4 | 0.281605 | 2(Loss) | true |
