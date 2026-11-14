
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5024.02 | 0.19286 | 742.035ms | 1691 | 320 | 122.636 | 320.991 | 0.413984 | 1.16003 | 4.3702 | 0.635127 | 0.000591366 | 2.95683e-05 | 7.39208e-06 | 1(Win) | true |
| simdjson (ondemand) | 4417.42 | 0.16965 | 746.026ms | 1691 | 160 | 61.3726 | 365.069 | 0.158963 | 1.29073 | 4.79243 | 0.644589 | 0.000694855 | 5.54406e-05 | 0 | 2(Loss) | true |
