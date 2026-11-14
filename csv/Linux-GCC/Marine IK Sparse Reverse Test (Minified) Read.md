
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3142.65 | 0.51235 | 7192.48ms | 1834197 | 160 | 1.30123e+09 | 556608 | 0.629875 | 1.63667 | 8.50401 | 1.52924 | 0.000657682 | 0.113275 | 2.51813e-06 | 1(Win) | true |
| simdjson (ondemand) | 2218.36 | 0.163756 | 5049.67ms | 1834197 | 320 | 5.33546e+08 | 788524 | 0.0881739 | 2.30018 | 12.8396 | 2.27677 | 0.00496616 | 0.150668 | 5.42131e-06 | 2(Loss) | true |
