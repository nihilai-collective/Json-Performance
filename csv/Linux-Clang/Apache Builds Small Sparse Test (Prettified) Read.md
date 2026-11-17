
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3684.98 | 0.0653026 | 805.086ms | 3370 | 4890 | 1586.21 | 872.158 | 0.0664488 | 1.45944 | 5.77745 | 0.982196 | 0.000710892 | 4.8121e-05 | 1.45637e-05 | 1(Win) | true |
| simdjson (ondemand) | 3058.41 | 0.100697 | 823.441ms | 3370 | 320 | 358.302 | 1050.83 | 0.0811196 | 1.74713 | 6.50564 | 1.02967 | 0.00264188 | 2.96736e-05 | 7.4184e-06 | 2(Loss) | true |
