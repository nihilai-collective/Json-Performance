
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4734.1 | 0.0400829 | 813.714ms | 5092 | 4890 | 826.665 | 1025.77 | 0.245894 | 1.13053 | 4.97604 | 0.690888 | 0.00115852 | 1.75904e-05 | 1.76708e-06 | 1(Win) | true |
| simdjson (ondemand) | 4641.05 | 0.049292 | 817.62ms | 5092 | 4890 | 1300.79 | 1046.34 | 0.0254368 | 1.15101 | 5.29478 | 0.663787 | 0.000940527 | 1.22491e-05 | 2.53013e-06 | 2(Loss) | true |
