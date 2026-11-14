
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2337.83 | 0.106957 | 821.04ms | 2632 | 160 | 211.001 | 1073.67 | 0.133707 | 2.28303 | 9.32371 | 1.7424 | 0.00152688 | 4.27432e-05 | 9.49848e-06 | 1(Win) | true |
| simdjson (ondemand) | 2090.83 | 0.0678999 | 834.138ms | 2632 | 160 | 106.314 | 1200.51 | 0.0573 | 2.54396 | 9.8712 | 1.76102 | 0.0021989 | 3.32447e-05 | 2.37462e-06 | 2(Loss) | true |
