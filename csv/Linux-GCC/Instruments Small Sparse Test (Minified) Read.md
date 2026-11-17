
----
### Instruments Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4480.08 | 0.046896 | 813.3ms | 4669 | 4890 | 1062.33 | 993.89 | 0.0757232 | 1.19551 | 5.19576 | 0.739559 | 0.00154725 | 3.95508e-05 | 1.31398e-05 | 1(Win) | true |
| simdjson (ondemand) | 4363.38 | 0.0800133 | 816.592ms | 4669 | 4890 | 3260.13 | 1020.47 | 0.0157858 | 1.22553 | 5.57061 | 0.702299 | 0.00129357 | 2.09361e-05 | 3.10975e-06 | 2(Loss) | true |
