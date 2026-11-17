
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1296.04 | 0.0342711 | 1155.47ms | 5092 | 4890 | 8063.14 | 3746.88 | 0.105721 | 4.01644 | 16.9538 | 3.13537 | 0.00337773 | 4.63456e-05 | 1.41366e-05 | 1(Win) | true |
| simdjson (ondemand) | 1277.57 | 0.0543271 | 1141.16ms | 5092 | 640 | 2729.11 | 3801.06 | 0.0222027 | 4.08095 | 17.0939 | 2.74897 | 0.00338889 | 2.88443e-05 | 5.83022e-06 | 2(Loss) | true |
