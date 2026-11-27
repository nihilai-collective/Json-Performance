
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5347.77 | 0.0978755 | 891.414ms | 9739 | 160 | 462.33 | 1736.77 | 0.0500461 | 0.985648 | 4.56371 | 0.745662 | 0.00155496 | 2.0536e-05 | 5.134e-06 | 1(Win) | true |
| simdjson (ondemand) | 4962.63 | 0.0709664 | 906.722ms | 9739 | 160 | 282.248 | 1871.56 | 0.147054 | 1.06076 | 4.94558 | 0.700893 | 0.00101011 | 7.05925e-06 | 6.4175e-07 | 2(Loss) | true |
