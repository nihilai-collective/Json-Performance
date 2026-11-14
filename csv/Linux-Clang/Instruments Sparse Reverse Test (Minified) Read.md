
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3303.2 | 0.154703 | 3841.42ms | 108313 | 640 | 1.49786e+06 | 31271.3 | 0.335901 | 1.5559 | 8.1892 | 1.44348 | 0.00150575 | 5.25099e-06 | 2.06289e-06 | 1(Win) | true |
| simdjson (ondemand) | 2625.36 | 0.0308991 | 4667.2ms | 108313 | 2560 | 378371 | 39345.2 | 0.286061 | 1.95646 | 10.3411 | 1.59589 | 0.00282828 | 7.4978e-06 | 3.25662e-06 | 2(Loss) | true |
