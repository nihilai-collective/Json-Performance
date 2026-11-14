
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2160.69 | 0.173115 | 1160.87ms | 9739 | 320 | 17720.1 | 4298.55 | 0.331856 | 2.40246 | 9.70099 | 1.74533 | 0.00194996 | 1.15515e-05 | 1.2835e-06 | 1(Win) | true |
| simdjson (ondemand) | 2132.71 | 0.0504366 | 1165.74ms | 9739 | 2560 | 12350.8 | 4354.94 | 0.0389402 | 2.41437 | 9.82878 | 1.6086 | 0.0015635 | 1.66053e-05 | 4.49225e-06 | 2(Loss) | true |
