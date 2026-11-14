
----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3936.5 | 0.0237948 | 9839.32ms | 676745 | 1280 | 1.94808e+06 | 163951 | 0.0863073 | 1.28749 | 5.93055 | 1.00905 | 0.00341042 | 0.00488033 | 6.07573e-06 | 1(Win) | true |
| simdjson (ondemand) | 3369.95 | 0.101704 | 5624.41ms | 676745 | 30 | 1.13815e+06 | 191514 | 0.207664 | 1.52817 | 6.48114 | 0.954434 | 0.00469842 | 0.00474856 | 3.15234e-06 | 2(Loss) | true |
