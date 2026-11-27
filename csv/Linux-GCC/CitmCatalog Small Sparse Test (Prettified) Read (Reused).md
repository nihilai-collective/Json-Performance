
----
### CitmCatalog Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8157.66 | 0.0319094 | 831.299ms | 9739 | 4890 | 645.422 | 1138.54 | 0.157514 | 0.649491 | 2.96817 | 0.372831 | 0.000525684 | 1.43836e-05 | 5.83743e-06 | 1(Win) | true |
| simdjson (ondemand) | 7182.78 | 0.063168 | 844.4ms | 9739 | 2560 | 1707.97 | 1293.07 | 0.0576117 | 0.73784 | 3.40877 | 0.363487 | 0.000420065 | 1.89717e-05 | 1.24339e-05 | 2(Loss) | true |
