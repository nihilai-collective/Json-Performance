
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4755.91 | 0.0782931 | 816.444ms | 5092 | 160 | 102.253 | 1021.07 | 0.0483796 | 1.12646 | 4.97604 | 0.690888 | 0.00106785 | 2.70031e-05 | 1.22742e-06 | 1(Win) | true |
| simdjson (ondemand) | 4415.62 | 0.0395264 | 822.216ms | 5092 | 2560 | 483.736 | 1099.76 | 0.030236 | 1.20806 | 5.29271 | 0.663216 | 0.000799048 | 1.68003e-05 | 2.07126e-06 | 2(Loss) | true |
