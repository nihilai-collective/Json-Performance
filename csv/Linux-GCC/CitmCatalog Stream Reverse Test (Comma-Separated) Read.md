
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 836.367 | 0.685982 | 8144.66ms | 4525119 | 40 | 5.01132e+10 | 5.15981e+06 | 0.0635479 | 6.06042 | 29.8375 | 6.04081 | 0.0152137 | 0.0776647 | 0.00514352 | 1(Win) | true |
| simdjson (ondemand) | 512.241 | 0.109227 | 6136.65ms | 4525119 | 30 | 2.54035e+09 | 8.42472e+06 | 0.179411 | 9.87359 | 46.4446 | 9.68143 | 0.028571 | 0.0929257 | 0.0122164 | 2(Loss) | true |
