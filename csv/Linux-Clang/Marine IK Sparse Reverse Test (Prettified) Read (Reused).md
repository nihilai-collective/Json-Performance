
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7706.94 | 0.116955 | 5815.64ms | 7351818 | 320 | 3.62251e+08 | 909730 | 0.56516 | 0.662884 | 3.07634 | 0.416909 | 0.00100953 | 0.0634913 | 0.00028141 | 1(Win) | true |
| simdjson (ondemand) | 6270.09 | 0.0854327 | 7098.08ms | 7351818 | 160 | 1.46019e+08 | 1.1182e+06 | 0.00199654 | 0.811175 | 4.06918 | 0.606495 | 0.000979991 | 0.0847872 | 8.99522e-06 | 2(Loss) | true |
