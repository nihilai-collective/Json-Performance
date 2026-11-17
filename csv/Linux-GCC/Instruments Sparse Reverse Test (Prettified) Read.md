
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4881.24 | 0.0541944 | 4319.4ms | 183677 | 4890 | 1.84955e+06 | 35886 | 0.0931482 | 1.0506 | 5.38262 | 0.894059 | 0.000864002 | 3.94687e-06 | 1.58654e-06 | 1(Win) | true |
| simdjson (ondemand) | 4045.82 | 0.0387379 | 5070.21ms | 183677 | 4890 | 1.37555e+06 | 43296 | 0.424853 | 1.26463 | 6.41805 | 0.98009 | 0.00215768 | 1.7747e-06 | 4.53138e-07 | 2(Loss) | true |
