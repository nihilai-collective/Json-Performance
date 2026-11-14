
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2234.12 | 0.478783 | 4601.53ms | 108313 | 80 | 3.92028e+06 | 46235.4 | 0.00913885 | 1(Win) | true |
| simdjson (ondemand) | 1379.77 | 0.193527 | 7683.81ms | 108313 | 4890 | 1.02645e+08 | 74864.3 | 0.345213 | 2(Loss) | true |
