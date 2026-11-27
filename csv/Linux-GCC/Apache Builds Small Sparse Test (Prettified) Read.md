
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4059.39 | 0.0659888 | 795.718ms | 3370 | 2560 | 698.746 | 791.716 | 0.0203235 | 1.32919 | 5.43056 | 0.877745 | 0.000301256 | 1.588e-05 | 5.33197e-06 | 1(Win) | true |
| simdjson (ondemand) | 3093.56 | 0.125151 | 822.572ms | 3370 | 1280 | 2163.82 | 1038.9 | 0.000827207 | 1.72598 | 6.45193 | 1.05816 | 0.000401984 | 3.33828e-05 | 8.80935e-06 | 2(Loss) | true |
