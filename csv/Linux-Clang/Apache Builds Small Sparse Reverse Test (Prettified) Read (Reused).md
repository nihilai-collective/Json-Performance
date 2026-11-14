
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3322.05 | 0.0423687 | 813.37ms | 3370 | 640 | 107.527 | 967.439 | 0.0803344 | 1.61533 | 7.04303 | 1.22463 | 0.000890208 | 1.48368e-05 | 4.6365e-07 | 1(Win) | true |
| simdjson (ondemand) | 3088.04 | 0.0948415 | 820.364ms | 3370 | 160 | 155.887 | 1040.75 | 0.104601 | 1.73383 | 7.14421 | 1.11662 | 0.00104043 | 4.45104e-05 | 9.273e-06 | 2(Loss) | true |
