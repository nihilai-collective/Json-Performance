
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2814.68 | 0.0230105 | 5456.06ms | 124597 | 2560 | 241574 | 42216.1 | 0.0347302 | 1.81589 | 8.69081 | 1.60163 | 0.00479576 | 3.91261e-06 | 9.53073e-07 | 1(Win) | true |
| simdjson (ondemand) | 2479.14 | 0.0995241 | 6009.29ms | 124597 | 160 | 364074 | 47929.9 | 0.0221629 | 2.07207 | 8.71633 | 1.53789 | 0.00601855 | 3.411e-06 | 6.01941e-07 | 2(Loss) | true |
