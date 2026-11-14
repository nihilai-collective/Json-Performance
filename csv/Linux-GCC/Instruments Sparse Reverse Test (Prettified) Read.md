
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4896.59 | 0.0169941 | 4318.51ms | 183677 | 4890 | 180729 | 35773.4 | 0.0550455 | 1.04896 | 5.38356 | 0.894255 | 0.000874519 | 1.63219e-06 | 4.0749e-07 | 1(Win) | true |
| simdjson (ondemand) | 4114.96 | 0.0388314 | 4979.12ms | 183677 | 2560 | 699495 | 42568.6 | 0.131097 | 1.24567 | 6.41572 | 0.979132 | 0.00202912 | 2.49461e-06 | 9.6552e-07 | 2(Loss) | true |
