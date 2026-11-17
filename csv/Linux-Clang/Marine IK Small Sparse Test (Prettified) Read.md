
----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10164.9 | 0.0245744 | 887.564ms | 18245 | 4890 | 865.279 | 1711.75 | 0.0492386 | 0.518437 | 2.5419 | 0.274431 | 0.000219451 | 8.86592e-06 | 9.07888e-07 | 1(Win) | true |
| simdjson (ondemand) | 9902.77 | 0.0983857 | 893.516ms | 18245 | 80 | 239.072 | 1757.06 | 0.00640232 | 0.532131 | 2.66117 | 0.28342 | 0.000210332 | 8.22143e-06 | 2.74048e-06 | 2(Loss) | true |
