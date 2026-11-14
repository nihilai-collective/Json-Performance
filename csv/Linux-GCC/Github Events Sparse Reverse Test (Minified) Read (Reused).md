
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5979.54 | 0.0449498 | 1591.2ms | 53331 | 4890 | 71480.7 | 8505.73 | 0.102676 | 0.860902 | 4.18293 | 0.667248 | 0.00170078 | 6.50719e-06 | 1.33058e-06 | 1(Win) | true |
| simdjson (ondemand) | 4332.29 | 0.0223223 | 1912.2ms | 53331 | 2560 | 17581 | 11739.9 | 0.00596557 | 1.19136 | 5.707 | 0.921059 | 0.00277124 | 3.74284e-06 | 3.2228e-07 | 2(Loss) | true |
