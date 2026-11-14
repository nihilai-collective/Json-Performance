
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3728.3 | 0.110332 | 800.357ms | 3370 | 2560 | 2315.7 | 862.024 | 0.00557404 | 1.44887 | 5.94392 | 0.933828 | 0.000430847 | 3.19918e-05 | 1.13594e-05 | 1(Win) | true |
| simdjson (ondemand) | 3079.02 | 0.148518 | 818.4ms | 3370 | 30 | 72.0966 | 1043.8 | 0.102086 | 1.73489 | 6.4635 | 1.05905 | 0.000544016 | 1.97824e-05 | 0 | 2(Loss) | true |
