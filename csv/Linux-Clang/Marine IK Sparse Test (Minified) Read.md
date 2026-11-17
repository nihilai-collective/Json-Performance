
----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4671.61 | 0.194915 | 9838.21ms | 1834197 | 160 | 8.52257e+07 | 374438 | 0.0735175 | 1.0979 | 6.28014 | 0.838105 | 0.00244447 | 0.0754577 | 1.21988e-06 | 1(Win) | true |
| simdjson (ondemand) | 4312.23 | 0.0832119 | 5247.47ms | 1834197 | 40 | 4.55743e+06 | 405644 | 0.0105747 | 1.17276 | 6.33085 | 0.867839 | 0.00351834 | 0.0749098 | 2.98496e-06 | 2(Loss) | true |
