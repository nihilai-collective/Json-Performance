
----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3988.24 | 0.0779542 | 2597.76ms | 108313 | 4890 | 1.99336e+06 | 25900 | 0.237058 | 0.761349 | 1(Win) | true |
| simdjson (ondemand) | 3281.37 | 0.39445 | 3160.96ms | 108313 | 160 | 2.46693e+06 | 31479.4 | 0.0535778 | 0.925566 | 2(Loss) | true |
