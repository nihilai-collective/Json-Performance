
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3202.77 | 0.0721709 | 867.536ms | 5092 | 4890 | 5855.44 | 1516.22 | 0.119288 | 1.6481 | 7.76984 | 1.38374 | 0.00253993 | 1.41768e-05 | 6.42573e-07 | 1(Win) | true |
| simdjson (ondemand) | 3170.21 | 0.0964351 | 869.692ms | 5092 | 160 | 349.133 | 1531.79 | 0.156516 | 1.67336 | 8.32698 | 1.3097 | 0.00224249 | 4.90966e-06 | 0 | 2(Loss) | true |
