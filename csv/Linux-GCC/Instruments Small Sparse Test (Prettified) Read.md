
----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6405.85 | 0.0423376 | 828.796ms | 7932 | 4890 | 1222.29 | 1180.88 | 0.119135 | 0.837429 | 3.84468 | 0.434317 | 0.000729385 | 1.24525e-05 | 2.39768e-06 | 1(Win) | true |
| Jsonifier (generic) | 6277.6 | 0.0580758 | 830.106ms | 7932 | 640 | 313.437 | 1205.01 | 0.166216 | 0.847633 | 3.6852 | 0.463944 | 0.000889396 | 2.9548e-06 | 0 | 2(Loss) | true |
