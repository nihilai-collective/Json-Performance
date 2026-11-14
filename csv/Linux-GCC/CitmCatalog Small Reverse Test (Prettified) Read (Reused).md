
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.24 | 0.0231553 | 1482.01ms | 9739 | 4890 | 13054.7 | 7056.32 | 0.0697598 | 3.93428 | 16.5523 | 3.29237 | 0.00412624 | 2.77173e-05 | 5.77443e-06 | 1(Win) | true |
| simdjson (ondemand) | 888.743 | 0.0769932 | 1805.89ms | 9739 | 320 | 20717.2 | 10450.5 | 0.0275628 | 5.81511 | 27.8316 | 5.522 | 0.00934035 | 3.27292e-05 | 5.77575e-06 | 2(Loss) | true |
