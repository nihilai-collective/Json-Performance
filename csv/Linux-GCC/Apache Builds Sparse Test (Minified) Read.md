
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.33 | 0.0476048 | 4334.71ms | 94653 | 2560 | 754352 | 36059.2 | 0.0646012 | 2.02224 | 9.5773 | 1.71249 | 0.00497251 | 3.83803e-06 | 1.38252e-06 | 1(Win) | true |
| simdjson (ondemand) | 1807.95 | 0.0321341 | 5704.05ms | 94653 | 1280 | 329488 | 49928.6 | 0.0124428 | 2.82643 | 10.6684 | 1.97307 | 0.00839203 | 5.48054e-06 | 2.07997e-06 | 2(Loss) | true |
