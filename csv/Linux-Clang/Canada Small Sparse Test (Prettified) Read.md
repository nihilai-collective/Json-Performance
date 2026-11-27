
----
### Canada Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11665.3 | 0.0852892 | 811.324ms | 11579 | 320 | 208.588 | 946.619 | 0.26878 | 0.461081 | 2.09111 | 0.225754 | 0.000172726 | 5.3977e-06 | 1.07954e-06 | 1(Win) | true |
| simdjson (ondemand) | 10956.3 | 0.0425809 | 816.061ms | 11579 | 2560 | 471.497 | 1007.87 | 0.107163 | 0.487649 | 2.36894 | 0.23154 | 0.000174953 | 8.97368e-06 | 2.69885e-06 | 2(Loss) | true |
