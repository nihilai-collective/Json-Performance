
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3137.56 | 0.372147 | 7123.08ms | 1834197 | 320 | 1.37749e+09 | 557512 | 0.558721 | 1.63376 | 8.50401 | 1.52924 | 0.000619345 | 0.113247 | 1.00095e-05 | 1(Win) | true |
| simdjson (ondemand) | 2286.09 | 0.535888 | 9798.91ms | 1834197 | 80 | 1.34506e+09 | 765160 | 0.049382 | 2.24543 | 12.8396 | 2.27677 | 0.00500727 | 0.150814 | 3.9595e-06 | 2(Loss) | true |
