
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3348.84 | 0.0728644 | 862.252ms | 5092 | 2560 | 2857.97 | 1450.09 | 0.106185 | 1.58459 | 7.76984 | 1.38374 | 0.0016037 | 2.24003e-05 | 8.82205e-06 | 1(Win) | true |
| simdjson (ondemand) | 3170.19 | 0.0691018 | 867.521ms | 5092 | 320 | 358.539 | 1531.81 | 0.146283 | 1.66724 | 8.32718 | 1.30931 | 0.00216455 | 1.4729e-05 | 3.68225e-06 | 2(Loss) | true |
