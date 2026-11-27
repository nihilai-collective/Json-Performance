
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3852.42 | 0.110903 | 803.153ms | 3370 | 1280 | 1095.7 | 834.251 | 0.375885 | 1.4022 | 5.67211 | 0.950149 | 0.00111392 | 1.11276e-05 | 3.7092e-06 | 1(Win) | true |
| simdjson (ondemand) | 3076.85 | 0.130009 | 824.806ms | 3370 | 1280 | 2360.49 | 1044.54 | 0.216923 | 1.73589 | 6.50267 | 1.02789 | 0.00186364 | 1.57641e-05 | 2.31825e-07 | 2(Loss) | true |
