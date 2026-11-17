
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5484.8 | 0.170293 | 795.947ms | 4630 | 640 | 1202.86 | 805.045 | 0.186945 | 0.986199 | 5.11577 | 0.797192 | 0.000647948 | 8.7743e-06 | 2.02484e-06 | 1(Win) | true |
| simdjson (ondemand) | 4550.05 | 0.127988 | 810.283ms | 4630 | 160 | 246.825 | 970.431 | 0.119006 | 1.17871 | 5.55032 | 0.810583 | 0.000647948 | 1.61987e-05 | 0 | 2(Loss) | true |
