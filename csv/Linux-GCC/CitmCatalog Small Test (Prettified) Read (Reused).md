
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2489.67 | 0.202625 | 1193.54ms | 9739 | 160 | 9142.24 | 3730.55 | 0.048227 | 2.08945 | 8.8006 | 1.51268 | 0.00145228 | 2.11777e-05 | 5.134e-06 | 1(Win) | true |
| simdjson (ondemand) | 2288.12 | 0.0502186 | 1167.77ms | 9739 | 640 | 2659.38 | 4059.15 | 0.193784 | 2.27363 | 9.13554 | 1.46884 | 0.00184712 | 1.81294e-05 | 2.24612e-06 | 2(Loss) | true |
