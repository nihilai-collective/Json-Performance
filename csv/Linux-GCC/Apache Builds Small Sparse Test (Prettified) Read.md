
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3811.09 | 0.107262 | 800.145ms | 3370 | 2560 | 2094.57 | 843.298 | 0.298175 | 1.41438 | 5.94392 | 0.933828 | 0.000298938 | 3.22237e-05 | 1.39095e-05 | 1(Win) | true |
| simdjson (ondemand) | 3044.41 | 0.114119 | 822.121ms | 3370 | 30 | 43.5402 | 1055.67 | 0.0284261 | 1.76403 | 6.46261 | 1.05846 | 0.000296736 | 2.96736e-05 | 0 | 2(Loss) | true |
