
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2977.42 | 0.299253 | 991.607ms | 8150 | 160 | 9764.11 | 2610.46 | 0.0220219 | 1.75322 | 7.62761 | 1.35988 | 0.00316564 | 1.30368e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2626.89 | 0.0692437 | 1025.33ms | 8150 | 1280 | 5372.82 | 2958.8 | 0.0525457 | 1.98837 | 8.86282 | 1.39571 | 0.00357813 | 1.90759e-05 | 3.93021e-06 | 2(Loss) | true |
