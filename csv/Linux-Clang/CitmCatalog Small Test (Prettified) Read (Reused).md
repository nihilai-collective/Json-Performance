
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2273.89 | 0.0443905 | 1175.45ms | 9739 | 4890 | 16076.1 | 4084.56 | 0.0156807 | 2.26606 | 9.52736 | 1.66188 | 0.00120289 | 4.31508e-05 | 1.82472e-05 | 1(Win) | true |
| simdjson (ondemand) | 2260.15 | 0.0429753 | 1176.12ms | 9739 | 4890 | 15251.1 | 4109.38 | 0.0512811 | 2.28288 | 9.54782 | 1.4721 | 0.0021756 | 4.01481e-05 | 1.92551e-05 | 2(Loss) | true |
