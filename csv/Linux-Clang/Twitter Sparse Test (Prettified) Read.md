
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7969.13 | 0.0820575 | 5061.89ms | 360584 | 1280 | 1.60486e+06 | 43151.5 | 0.0680369 | 0.639412 | 2.99814 | 0.371775 | 0.000775118 | 1.8828e-06 | 8.3415e-07 | 1(Win) | true |
| simdjson (ondemand) | 7357.03 | 0.054515 | 5404.81ms | 360584 | 1280 | 831094 | 46741.6 | 0.178129 | 0.689234 | 3.19568 | 0.335546 | 0.00103855 | 3.4731e-06 | 1.54697e-06 | 2(Loss) | true |
