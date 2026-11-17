
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3895.38 | 0.0558415 | 4285.74ms | 124597 | 640 | 185700 | 30504.1 | 0.0571113 | 1.31109 | 6.12951 | 1.04542 | 0.00306955 | 4.72774e-06 | 2.67111e-06 | 1(Win) | true |
| simdjson (ondemand) | 3118.57 | 0.0244018 | 5050.36ms | 124597 | 2560 | 221303 | 38102.3 | 0.103463 | 1.62773 | 6.91474 | 1.10383 | 0.00479834 | 8.76576e-06 | 5.00677e-06 | 2(Loss) | true |
