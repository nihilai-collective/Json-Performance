
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5449.95 | 0.0811759 | 788.92ms | 4630 | 4890 | 2115.15 | 810.193 | 0.184549 | 0.988915 | 5.06134 | 0.792873 | 0.000650642 | 1.77115e-05 | 2.34092e-06 | 1(Win) | true |
| simdjson (ondemand) | 4291.87 | 0.129656 | 813.087ms | 4630 | 1280 | 2277.54 | 1028.81 | 0.324864 | 1.24573 | 5.55054 | 0.812311 | 0.000648792 | 1.26552e-05 | 0 | 2(Loss) | true |
