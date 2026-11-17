
----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5636.51 | 0.130466 | 745.6ms | 2158 | 640 | 145.23 | 365.125 | 0.24108 | 1.01692 | 3.82484 | 0.510658 | 0.000621235 | 1.30329e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5324.78 | 0.297144 | 750.772ms | 2158 | 30 | 39.569 | 386.5 | 0.172191 | 1.08386 | 4.02224 | 0.515292 | 0.00077232 | 0 | 0 | 2(Loss) | true |
