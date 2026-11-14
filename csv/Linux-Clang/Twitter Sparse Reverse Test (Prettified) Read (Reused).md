
----
### Twitter Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5923.74 | 0.0250025 | 6587.17ms | 360584 | 2560 | 539296 | 58051.1 | 0.165738 | 0.864932 | 4.32478 | 0.65242 | 0.00144112 | 3.17085e-06 | 1.32922e-06 | 1(Win) | true |
| simdjson (ondemand) | 5073.8 | 0.0985633 | 7615.75ms | 360584 | 80 | 356999 | 67775.6 | 0.112451 | 0.999326 | 4.9762 | 0.691724 | 0.00182579 | 1.14398e-06 | 2.77328e-07 | 2(Loss) | true |
