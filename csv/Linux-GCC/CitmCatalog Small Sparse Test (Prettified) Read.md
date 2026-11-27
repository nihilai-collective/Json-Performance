
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7848.58 | 0.0362488 | 835.888ms | 9739 | 4890 | 899.795 | 1183.38 | 0.117034 | 0.678291 | 3.02639 | 0.385666 | 0.000762498 | 1.77433e-05 | 8.31519e-06 | 1(Win) | true |
| simdjson (ondemand) | 6891.36 | 0.114939 | 852.268ms | 9739 | 40 | 95.9872 | 1347.75 | 0.0160788 | 0.755976 | 3.46904 | 0.37663 | 0.000551905 | 7.701e-06 | 2.567e-06 | 2(Loss) | true |
