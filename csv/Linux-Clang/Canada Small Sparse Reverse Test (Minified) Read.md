
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5058.09 | 0.123169 | 801.204ms | 4630 | 2560 | 2959.61 | 872.961 | 0.370532 | 1.06482 | 5.1527 | 0.805184 | 0.000648201 | 2.51417e-05 | 1.07148e-05 | 1(Win) | true |
| simdjson (ondemand) | 4516.78 | 0.197063 | 811.641ms | 4630 | 640 | 2375.18 | 977.58 | 0.0263795 | 1.18717 | 5.58726 | 0.818575 | 0.000647948 | 1.45113e-05 | 6.74946e-07 | 2(Loss) | true |
