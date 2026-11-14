
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4784.78 | 0.0600894 | 9590.45ms | 1834197 | 160 | 7.72118e+06 | 365581 | 0.024532 | 1.07219 | 6.27992 | 0.838056 | 0.00220732 | 0.075505 | 1.92182e-06 | 1(Win) | true |
| simdjson (ondemand) | 4352.38 | 0.0428445 | 5209.37ms | 1834197 | 640 | 1.89762e+07 | 401901 | 0.175677 | 1.17061 | 6.33061 | 0.867784 | 0.00335713 | 0.0754283 | 2.39461e-06 | 2(Loss) | true |
