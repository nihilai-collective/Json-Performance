
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4598.74 | 0.152316 | 9923.44ms | 1834197 | 320 | 1.07412e+08 | 380371 | 0.141191 | 1.10705 | 6.27992 | 0.838056 | 0.00255981 | 0.0754279 | 3.3683e-06 | 1(Win) | true |
| simdjson (ondemand) | 4327.83 | 0.0588452 | 5234.54ms | 1834197 | 320 | 1.81019e+07 | 404181 | 0.133486 | 1.17345 | 6.33063 | 0.86779 | 0.00353133 | 0.0748776 | 3.81127e-06 | 2(Loss) | true |
