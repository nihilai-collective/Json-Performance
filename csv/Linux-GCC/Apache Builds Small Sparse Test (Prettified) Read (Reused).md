
----
### Apache Builds Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4575.1 | 0.0887824 | 788.991ms | 3370 | 640 | 248.938 | 702.472 | 0.298051 | 1.19091 | 5.14421 | 0.74273 | 0.000828542 | 2.73553e-05 | 8.80935e-06 | 1(Win) | true |
| simdjson (ondemand) | 3507.79 | 0.0845183 | 809.458ms | 3370 | 2560 | 1535.09 | 916.213 | 0.0438904 | 1.53082 | 5.66113 | 0.866172 | 0.000885687 | 2.79349e-05 | 3.7092e-06 | 2(Loss) | true |
