
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3285.17 | 0.056525 | 813.925ms | 3370 | 4890 | 1495.32 | 978.301 | 0.146817 | 1.63208 | 6.95312 | 1.1997 | 0.000891543 | 2.56686e-05 | 4.4298e-06 | 1(Win) | true |
| simdjson (ondemand) | 3043.55 | 0.0433421 | 823.851ms | 3370 | 640 | 134.06 | 1055.96 | 0.00103577 | 1.75702 | 7.03828 | 1.15786 | 0.00133763 | 1.90096e-05 | 2.7819e-06 | 2(Loss) | true |
