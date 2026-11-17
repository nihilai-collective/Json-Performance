
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2516.23 | 0.152996 | 904.377ms | 4926 | 80 | 652.734 | 1867 | 0.0120529 | 2.08547 | 9.33151 | 1.60495 | 0.00160881 | 2.79131e-05 | 1.77629e-05 | 1(Win) | true |
| simdjson (ondemand) | 2120.95 | 0.0851062 | 943.99ms | 4926 | 80 | 284.276 | 2214.95 | 0.0180558 | 2.47361 | 9.99513 | 1.64373 | 0.00285221 | 5.07511e-06 | 2.53756e-06 | 2(Loss) | true |
