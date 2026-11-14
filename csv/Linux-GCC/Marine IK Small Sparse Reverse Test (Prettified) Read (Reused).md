
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7988.2 | 0.113427 | 937.897ms | 18245 | 80 | 488.331 | 2178.19 | 0.00516458 | 0.657339 | 3.20066 | 0.447355 | 0.000329542 | 9.59167e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5818.21 | 0.0305545 | 1017.69ms | 18245 | 160 | 133.592 | 2990.57 | 0.0309401 | 0.897583 | 4.37649 | 0.631461 | 0.000343245 | 9.93423e-06 | 6.85119e-07 | 2(Loss) | true |
