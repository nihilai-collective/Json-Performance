
----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3253.18 | 0.128879 | 790.342ms | 2632 | 1280 | 1265.69 | 771.574 | 0.198972 | 1.66078 | 7.05775 | 1.16641 | 0.000384688 | 2.49335e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2393.95 | 0.0801174 | 818.044ms | 2632 | 160 | 112.906 | 1048.51 | 0.0256383 | 2.23201 | 8.10904 | 1.3883 | 0.00167648 | 1.8997e-05 | 0 | 2(Loss) | true |
