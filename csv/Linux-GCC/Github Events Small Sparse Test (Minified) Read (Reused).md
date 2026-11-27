
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5568.23 | 0.190079 | 742.85ms | 1691 | 160 | 48.489 | 289.619 | 0.00647361 | 1.04842 | 3.82141 | 0.571851 | 0.00116056 | 7.39208e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4339.08 | 0.0935056 | 751.757ms | 1691 | 2560 | 309.176 | 371.66 | 0.149996 | 1.31636 | 4.78001 | 0.647546 | 0.00114462 | 7.04557e-05 | 3.21093e-05 | 2(Loss) | true |
