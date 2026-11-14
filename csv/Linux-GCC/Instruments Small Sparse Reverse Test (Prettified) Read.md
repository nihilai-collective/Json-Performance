
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4730.28 | 0.137638 | 873.6ms | 7932 | 1280 | 6201.2 | 1599.17 | 0.0276922 | 1.124 | 5.0474 | 0.816944 | 0.000897669 | 1.87138e-05 | 6.59906e-06 | 1(Win) | true |
| simdjson (ondemand) | 3882.44 | 0.0298967 | 907.03ms | 7932 | 2560 | 868.646 | 1948.4 | 0.161229 | 1.35406 | 6.12607 | 0.929778 | 0.0016442 | 1.31981e-05 | 1.77288e-06 | 2(Loss) | true |
