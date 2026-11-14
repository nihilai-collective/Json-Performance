
----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9854.19 | 0.158715 | 898.198ms | 18245 | 40 | 314.153 | 1765.72 | 0.0826595 | 0.535625 | 2.46435 | 0.263305 | 0.000109619 | 4.11072e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9809.4 | 0.0603922 | 891.334ms | 18245 | 2560 | 2937.69 | 1773.79 | 0.0341446 | 0.537211 | 2.8028 | 0.284187 | 0.00011844 | 7.36503e-06 | 1.39165e-06 | 2(Loss) | true |
