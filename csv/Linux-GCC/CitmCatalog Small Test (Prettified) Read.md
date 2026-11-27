
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2227.05 | 0.099206 | 1141.3ms | 9739 | 320 | 5477.63 | 4170.46 | 0.0265329 | 2.33368 | 9.6323 | 1.71619 | 0.00141345 | 8.40692e-05 | 4.65269e-05 | 1(Win) | true |
| simdjson (ondemand) | 2049.83 | 0.136823 | 1175.67ms | 9739 | 320 | 12298.9 | 4531.03 | 0.00131039 | 2.53119 | 9.93398 | 1.66834 | 0.00157068 | 3.81841e-05 | 1.7969e-05 | 2(Loss) | true |
