
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3926.73 | 0.0183252 | 4246.21ms | 124597 | 4890 | 150370 | 30260.6 | 0.197073 | 1.30172 | 6.12549 | 1.04417 | 0.00292355 | 7.24134e-06 | 3.90133e-06 | 1(Win) | true |
| simdjson (ondemand) | 3125.06 | 0.0934808 | 4992.62ms | 124597 | 160 | 202146 | 38023.3 | 0.077068 | 1.64104 | 6.891 | 1.09639 | 0.00436537 | 2.40776e-06 | 1.50485e-07 | 2(Loss) | true |
