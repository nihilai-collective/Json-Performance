
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9957.32 | 0.0624411 | 905.207ms | 18245 | 160 | 190.487 | 1747.44 | 0.100046 | 0.520018 | 2.63798 | 0.278158 | 0.000114072 | 7.19375e-06 | 6.85119e-07 | 1(Win) | true |
| Jsonifier (generic) | 9688.18 | 0.219485 | 909.234ms | 18245 | 160 | 2486.19 | 1795.98 | 0.00939686 | 0.538221 | 2.51981 | 0.269498 | 0.000193204 | 1.09619e-05 | 4.79583e-06 | 2(Loss) | true |
