
----
### Random Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3518.14 | 0.0530073 | 9783.44ms | 676745 | 1280 | 1.21034e+07 | 183448 | 0.00304209 | 1.44102 | 6.78443 | 1.11455 | 0.00380622 | 0.00147277 | 1.88056e-05 | 1(Win) | true |
| simdjson (ondemand) | 3007.44 | 0.0446316 | 5681.11ms | 676745 | 640 | 5.87114e+06 | 214599 | 0.0491863 | 1.69886 | 7.01045 | 1.11296 | 0.00462198 | 0.00347399 | 5.5343e-06 | 2(Loss) | true |
