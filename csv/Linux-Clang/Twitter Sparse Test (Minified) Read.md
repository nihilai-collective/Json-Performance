
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7010.45 | 0.130175 | 4341.19ms | 264040 | 320 | 699605 | 35919 | 0.034006 | 0.722546 | 3.47659 | 0.478159 | 0.000943453 | 1.18353e-06 | 3.31389e-07 | 1(Win) | true |
| simdjson (ondemand) | 5921.03 | 0.054075 | 4984.27ms | 264040 | 640 | 338468 | 42527.8 | 0.0359784 | 0.853965 | 3.88683 | 0.43569 | 0.00115563 | 2.29605e-06 | 9.34991e-07 | 2(Loss) | true |
