
----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10048.9 | 0.0764443 | 892.346ms | 18245 | 160 | 280.327 | 1731.52 | 0.0883558 | 0.524855 | 2.46424 | 0.26325 | 0.000110304 | 1.19896e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 9651.17 | 0.0166853 | 898.073ms | 18245 | 1280 | 115.825 | 1802.87 | 0.201312 | 0.545829 | 2.80269 | 0.283968 | 0.000113987 | 5.86633e-06 | 1.7128e-07 | 2(Loss) | true |
