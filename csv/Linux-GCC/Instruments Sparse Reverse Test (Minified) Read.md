
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3400.86 | 0.100309 | 3766.64ms | 108313 | 160 | 148519 | 30373.3 | 0.0499866 | 1.51275 | 8.05213 | 1.45575 | 0.00144875 | 3.98152e-06 | 6.34735e-07 | 1(Win) | true |
| simdjson (ondemand) | 2650.35 | 0.0269393 | 4629.89ms | 108313 | 4890 | 539056 | 38974.2 | 0.0402458 | 1.934 | 9.92138 | 1.62881 | 0.00342744 | 5.84348e-06 | 2.99443e-06 | 2(Loss) | true |
