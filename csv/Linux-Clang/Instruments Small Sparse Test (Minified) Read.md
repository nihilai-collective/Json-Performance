
----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4357.92 | 0.322586 | 816.501ms | 4669 | 40 | 434.551 | 1021.75 | 0.125759 | 1.2292 | 5.1722 | 0.76269 | 0.00114586 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4179.39 | 0.0814367 | 817.986ms | 4669 | 1280 | 963.545 | 1065.4 | 0.0990434 | 1.28208 | 5.63868 | 0.702292 | 0.00154627 | 2.30911e-05 | 0 | 2(Loss) | true |
