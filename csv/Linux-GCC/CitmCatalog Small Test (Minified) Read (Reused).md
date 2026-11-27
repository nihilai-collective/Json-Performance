
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1440.96 | 0.0306478 | 1097.58ms | 5092 | 2560 | 2730.95 | 3370.06 | 0.00561038 | 3.61684 | 15.1208 | 2.77258 | 0.00142311 | 8.37711e-05 | 3.59786e-05 | 1(Win) | true |
| simdjson (ondemand) | 1259.36 | 0.0467933 | 1142.88ms | 5092 | 2560 | 8334.59 | 3856.02 | 0.129003 | 4.11217 | 16.2231 | 2.75648 | 0.00260933 | 0.000165471 | 9.35904e-05 | 2(Loss) | true |
