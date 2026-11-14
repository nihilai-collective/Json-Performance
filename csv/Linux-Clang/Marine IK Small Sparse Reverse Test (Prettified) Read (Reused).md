
----
### Marine IK Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7530 | 0.0302402 | 948.547ms | 18245 | 320 | 156.249 | 2310.73 | 0.0514994 | 0.6963 | 3.2866 | 0.45618 | 0.000274048 | 8.05015e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6335.89 | 0.0288453 | 993.47ms | 18245 | 160 | 100.402 | 2746.22 | 0.0514078 | 0.82557 | 4.25366 | 0.629104 | 0.000361743 | 2.05536e-05 | 6.85119e-07 | 2(Loss) | true |
