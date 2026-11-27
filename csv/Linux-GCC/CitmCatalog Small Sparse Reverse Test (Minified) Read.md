
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3184.57 | 0.0553202 | 871.419ms | 5092 | 2560 | 1821.73 | 1524.89 | 0.145623 | 1.65421 | 7.60055 | 1.39277 | 0.00349975 | 3.56718e-05 | 2.03291e-05 | 1(Win) | true |
| simdjson (ondemand) | 2905.49 | 0.0909072 | 885.756ms | 5092 | 1280 | 2954.93 | 1671.36 | 0.0171986 | 1.81351 | 8.32954 | 1.31383 | 0.00214322 | 4.18856e-05 | 2.07126e-05 | 2(Loss) | true |
