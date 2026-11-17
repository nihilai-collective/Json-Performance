
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2168.28 | 0.0566311 | 1160.23ms | 9739 | 160 | 941.522 | 4283.51 | 0.0183811 | 2.3985 | 9.81158 | 1.60659 | 0.00125462 | 1.41185e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 2157.34 | 0.068658 | 1162.36ms | 9739 | 1280 | 11183.7 | 4305.23 | 0.0800348 | 2.39655 | 9.74421 | 1.75638 | 0.00203194 | 2.19799e-05 | 4.25159e-06 | 2(Loss) | true |
