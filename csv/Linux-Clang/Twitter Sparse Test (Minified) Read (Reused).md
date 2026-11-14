
----
### Twitter Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7220.96 | 0.115361 | 4278.37ms | 264040 | 320 | 517864 | 34871.8 | 0.0215744 | 0.699111 | 3.39322 | 0.459385 | 0.000943619 | 2.87598e-06 | 8.28473e-07 | 1(Win) | true |
| simdjson (ondemand) | 6098.95 | 0.199604 | 4905.52ms | 264040 | 160 | 1.08665e+06 | 41287.1 | 0.105835 | 0.828942 | 3.80332 | 0.416939 | 0.00112537 | 1.96466e-06 | 6.86449e-07 | 2(Loss) | true |
