
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1210.94 | 0.0763902 | 1131.11ms | 5092 | 160 | 1501.51 | 4010.2 | 0.0408501 | 4.297 | 17.4683 | 3.31918 | 0.00340117 | 5.27789e-05 | 7.36449e-06 | 1(Win) | true |
| simdjson (ondemand) | 1203.17 | 0.0850857 | 1136.26ms | 5092 | 40 | 471.733 | 4036.1 | 0.1262 | 4.3242 | 17.5142 | 3.01417 | 0.00237137 | 1.96386e-05 | 0 | 2(Loss) | true |
