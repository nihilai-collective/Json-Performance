
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7823.84 | 0.121854 | 5156.04ms | 360584 | 80 | 229479 | 43952.8 | 0.1882 | 0.653764 | 3.11489 | 0.361203 | 0.00121151 | 4.92257e-06 | 3.67459e-06 | 1(Win) | true |
| simdjson (ondemand) | 7295.24 | 0.0254124 | 5442.2ms | 360584 | 2560 | 367337 | 47137.6 | 0.0377753 | 0.692906 | 3.31676 | 0.338541 | 0.000753346 | 2.94553e-06 | 1.47005e-06 | 2(Loss) | true |
