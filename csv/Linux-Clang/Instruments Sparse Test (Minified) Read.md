
----
### Instruments Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4713.76 | 0.022571 | 2920.55ms | 108313 | 1280 | 31314 | 21913.6 | 0.0482309 | 1.09422 | 5.5397 | 0.85313 | 0.000895747 | 3.45498e-06 | 9.2325e-07 | 1(Win) | true |
| simdjson (ondemand) | 4211.19 | 0.0245377 | 3171.04ms | 108313 | 4890 | 177145 | 24528.8 | 0.0706895 | 1.21987 | 6.09758 | 0.770028 | 0.0017308 | 4.99008e-06 | 2.40914e-06 | 2(Loss) | true |
