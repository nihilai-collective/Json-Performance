
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5036.37 | 0.0565752 | 9065.22ms | 1834197 | 320 | 1.23555e+07 | 347319 | 0.0279303 | 1.01602 | 5.69871 | 0.827937 | 0.000438671 | 0.0755488 | 1.82812e-06 | 1(Win) | true |
| simdjson (ondemand) | 4247.12 | 0.0551238 | 5321.88ms | 1834197 | 320 | 1.64941e+07 | 411861 | 0.0636754 | 1.19755 | 6.52899 | 0.874436 | 0.00498321 | 0.0754747 | 1.49077e-06 | 2(Loss) | true |
