
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3130.65 | 0.0717477 | 854.12ms | 4669 | 4890 | 5092.18 | 1422.29 | 0.626987 | 1.69058 | 7.65175 | 1.31292 | 0.00149763 | 2.19435e-05 | 1.48918e-06 | 1(Win) | true |
| simdjson (ondemand) | 2572.96 | 0.0310858 | 903.385ms | 4669 | 1280 | 370.437 | 1730.57 | 0.179756 | 2.04917 | 9.79225 | 1.53116 | 0.0023215 | 2.87803e-05 | 3.84852e-06 | 2(Loss) | true |
