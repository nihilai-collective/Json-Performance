
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7591.45 | 0.0528932 | 952.781ms | 18245 | 4890 | 7186.98 | 2292.02 | 0.170152 | 0.68516 | 3.16839 | 0.468734 | 0.000279282 | 1.4033e-05 | 4.59548e-06 | 1(Win) | true |
| simdjson (ondemand) | 6577.94 | 0.032681 | 986.619ms | 18245 | 4890 | 3654.34 | 2645.17 | 0.11744 | 0.792717 | 4.39819 | 0.636613 | 0.000240534 | 7.92441e-06 | 9.19097e-07 | 2(Loss) | true |
