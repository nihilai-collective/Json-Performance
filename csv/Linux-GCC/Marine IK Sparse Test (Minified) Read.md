
----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5052.31 | 0.022942 | 9065.96ms | 1834197 | 1280 | 8.07576e+06 | 346223 | 0.0502428 | 1.01517 | 5.6989 | 0.827984 | 0.000456594 | 0.0755813 | 2.46659e-06 | 1(Win) | true |
| simdjson (ondemand) | 4279.38 | 0.0811345 | 5307.64ms | 1834197 | 640 | 7.03917e+07 | 408757 | 0.0277412 | 1.19595 | 6.52919 | 0.874483 | 0.00489369 | 0.0754919 | 3.04629e-06 | 2(Loss) | true |
