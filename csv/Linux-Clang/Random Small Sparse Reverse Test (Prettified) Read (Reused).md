
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2965.61 | 0.0751052 | 990.331ms | 8150 | 1280 | 4959.49 | 2620.86 | 0.0357238 | 1.76227 | 7.62761 | 1.35988 | 0.00296281 | 2.05138e-05 | 2.68405e-06 | 1(Win) | true |
| simdjson (ondemand) | 2663.71 | 0.0574574 | 1019.3ms | 8150 | 160 | 449.733 | 2917.91 | 0.026339 | 1.96153 | 8.85804 | 1.39472 | 0.00295322 | 3.60429e-05 | 3.83436e-06 | 2(Loss) | true |
