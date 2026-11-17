
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5459.36 | 0.0672786 | 793.725ms | 4630 | 4890 | 1447.91 | 808.797 | 0.121112 | 0.989099 | 5.06134 | 0.792873 | 0.000648346 | 1.01587e-05 | 2.29675e-06 | 1(Win) | true |
| simdjson (ondemand) | 4343.41 | 0.163997 | 815.166ms | 4630 | 1280 | 3557.82 | 1016.6 | 0.102622 | 1.23218 | 5.55076 | 0.811879 | 0.000648792 | 8.26809e-06 | 6.74946e-07 | 2(Loss) | true |
