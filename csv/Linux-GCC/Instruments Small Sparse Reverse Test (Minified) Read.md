
----
### Instruments Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3185.17 | 0.0682638 | 857.793ms | 4669 | 1280 | 1165.66 | 1397.95 | 0.0252107 | 1.66296 | 7.48147 | 1.32255 | 0.00153757 | 2.87803e-05 | 1.10436e-05 | 1(Win) | true |
| simdjson (ondemand) | 2587.26 | 0.223671 | 890.274ms | 4669 | 640 | 9483.51 | 1721.01 | 0.0356675 | 2.06789 | 9.48319 | 1.55365 | 0.00291718 | 3.24614e-05 | 1.53941e-05 | 2(Loss) | true |
