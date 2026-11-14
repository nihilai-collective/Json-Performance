
----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5260.22 | 0.0820642 | 763.27ms | 2821 | 640 | 112.742 | 511.445 | 0.0626681 | 1.05509 | 3.9089 | 0.502659 | 0.000708968 | 1.82781e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5209.73 | 0.102633 | 764.239ms | 2821 | 2560 | 719.106 | 516.402 | 0.0973725 | 1.06604 | 4.15349 | 0.45374 | 0.000361685 | 1.05238e-05 | 2.07706e-06 | 2(Loss) | true |
