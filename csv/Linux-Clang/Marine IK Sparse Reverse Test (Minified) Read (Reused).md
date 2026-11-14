
----
### Marine IK Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3399.85 | 0.199842 | 6654.39ms | 1834197 | 320 | 3.38295e+08 | 514501 | 0.0606531 | 1.51383 | 8.73463 | 1.53929 | 0.00218296 | 0.113154 | 1.08358e-06 | 1(Win) | true |
| simdjson (ondemand) | 2399.63 | 0.293955 | 9246.66ms | 1834197 | 320 | 1.46932e+09 | 728957 | 0.140738 | 2.12772 | 12.6412 | 2.27006 | 0.00331183 | 0.150211 | 2.96622e-06 | 2(Loss) | true |
