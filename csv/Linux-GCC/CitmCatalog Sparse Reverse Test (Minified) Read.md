
----
### CitmCatalog Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3088.01 | 0.0692061 | 8286.42ms | 500299 | 80 | 914706 | 154508 | 0.0612236 | 1.66472 | 9.43991 | 1.76394 | 0.0021366 | 2.86828e-05 | 1.09934e-06 | 1(Win) | true |
| simdjson (ondemand) | 2986.67 | 0.0448546 | 8571.59ms | 500299 | 640 | 3.2861e+06 | 159751 | 0.139619 | 1.70997 | 10.1914 | 1.7315 | 0.00228666 | 2.06845e-05 | 5.01575e-06 | 2(Loss) | true |
