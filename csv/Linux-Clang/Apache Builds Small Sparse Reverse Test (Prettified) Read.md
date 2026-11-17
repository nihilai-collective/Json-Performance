
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2765.47 | 0.0716848 | 833.331ms | 3370 | 2560 | 1776.71 | 1162.15 | 0.131218 | 1.92059 | 7.87389 | 1.42018 | 0.00130471 | 4.86832e-05 | 1.78505e-05 | 1(Win) | true |
| simdjson (ondemand) | 2534.81 | 0.0456766 | 840.976ms | 3370 | 4890 | 1640.08 | 1267.9 | 0.205384 | 2.09406 | 7.98368 | 1.31543 | 0.00339644 | 3.50136e-05 | 4.91526e-06 | 2(Loss) | true |
