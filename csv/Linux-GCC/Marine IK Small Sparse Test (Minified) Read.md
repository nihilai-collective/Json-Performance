
----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4031.6 | 0.0988864 | 836.369ms | 4604 | 2560 | 2969.14 | 1089.08 | 0.0266425 | 1.32146 | 6.24957 | 0.926152 | 0.000438562 | 1.76477e-05 | 2.96956e-06 | 1(Win) | true |
| simdjson (ondemand) | 3800.21 | 0.0846591 | 832.852ms | 4604 | 160 | 153.082 | 1155.39 | 0.0996329 | 1.40354 | 7.04909 | 0.976542 | 0.000435762 | 9.50261e-06 | 0 | 2(Loss) | true |
