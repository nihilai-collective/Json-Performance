
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1224.94 | 0.0338715 | 1485.01ms | 9739 | 2560 | 16885.2 | 7582.25 | 0.0554956 | 4.23161 | 17.5024 | 3.52083 | 0.00389033 | 8.94439e-05 | 4.94147e-05 | 1(Win) | true |
| simdjson (ondemand) | 852.547 | 0.036246 | 1811.8ms | 9739 | 1280 | 19958.2 | 10894.2 | 0.0730421 | 6.06031 | 28.6795 | 5.72656 | 0.00899428 | 3.36116e-05 | 9.22515e-06 | 2(Loss) | true |
