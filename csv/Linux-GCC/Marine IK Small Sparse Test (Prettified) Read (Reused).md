
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10977.7 | 0.082944 | 877.716ms | 18245 | 2560 | 4424.61 | 1585.01 | 0.407333 | 0.478118 | 2.3875 | 0.276076 | 0.00011069 | 1.29102e-05 | 4.11072e-06 | 1(Win) | true |
| simdjson (ondemand) | 9774.22 | 0.0366269 | 901.54ms | 18245 | 320 | 136.042 | 1780.17 | 0.0829638 | 0.538785 | 2.78224 | 0.279857 | 0.000112702 | 1.31885e-05 | 2.91176e-06 | 2(Loss) | true |
