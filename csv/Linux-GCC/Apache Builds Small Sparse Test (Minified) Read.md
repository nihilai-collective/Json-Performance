
----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3542.3 | 0.114259 | 797.609ms | 2632 | 160 | 104.883 | 708.6 | 0.0229273 | 1.52929 | 6.37766 | 1.09195 | 0.000379939 | 4.27432e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2441.52 | 0.081187 | 822.514ms | 2632 | 160 | 111.466 | 1028.08 | 0.470309 | 2.19148 | 8.09119 | 1.3883 | 0.000384688 | 2.37462e-05 | 2.37462e-06 | 2(Loss) | true |
