
----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12609.3 | 0.0685112 | 799.573ms | 11579 | 160 | 57.5975 | 875.75 | 0.139685 | 0.427326 | 2.10459 | 0.210899 | 0.000172726 | 1.07954e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 11083.5 | 0.0982576 | 810.07ms | 11579 | 160 | 153.336 | 996.312 | 0.0238322 | 0.483755 | 2.36696 | 0.231108 | 0.000179204 | 1.72726e-05 | 3.23862e-06 | 2(Loss) | true |
