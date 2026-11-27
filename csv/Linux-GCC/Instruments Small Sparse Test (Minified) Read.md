
----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4945.68 | 0.0542839 | 807.356ms | 4669 | 4890 | 1168.01 | 900.321 | 0.0392362 | 1.08261 | 4.92846 | 0.735918 | 0.0010751 | 1.69065e-05 | 5.43111e-06 | 1(Win) | true |
| simdjson (ondemand) | 4389.6 | 0.0331439 | 819.174ms | 4669 | 2560 | 289.365 | 1014.38 | 0.0221475 | 1.21358 | 5.52966 | 0.697794 | 0.00114878 | 2.27565e-05 | 5.18714e-06 | 2(Loss) | true |
