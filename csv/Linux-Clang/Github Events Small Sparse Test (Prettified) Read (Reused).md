
----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5717.46 | 0.110365 | 745.736ms | 2158 | 4890 | 771.741 | 359.955 | 0.147134 | 1.00648 | 3.71038 | 0.531048 | 0.000840739 | 3.23142e-05 | 1.42145e-06 | 1(Win) | true |
| simdjson (ondemand) | 5474.48 | 0.162853 | 745.644ms | 2158 | 320 | 119.939 | 375.931 | 0.0349011 | 1.05647 | 3.96437 | 0.507888 | 0.00092244 | 2.8962e-05 | 0 | 2(Loss) | true |
