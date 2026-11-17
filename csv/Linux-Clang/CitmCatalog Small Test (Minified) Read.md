
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.82 | 0.0370675 | 1149.91ms | 5092 | 4890 | 11819.2 | 4194.17 | 0.095088 | 4.46363 | 18.4561 | 3.51458 | 0.00301564 | 5.06027e-05 | 2.06828e-05 | 1(Win) | true |
| simdjson (ondemand) | 1136.8 | 0.0387349 | 1154.74ms | 5092 | 4890 | 13388.2 | 4271.74 | 0.102847 | 4.53359 | 18.4456 | 3.09412 | 0.00350901 | 6.93176e-05 | 3.05624e-05 | 2(Loss) | true |
