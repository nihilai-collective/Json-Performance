
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7573.07 | 0.0514819 | 837.524ms | 9739 | 4890 | 1949.41 | 1226.43 | 0.0107927 | 0.701572 | 3.08289 | 0.373144 | 0.000666853 | 1.35437e-05 | 3.69564e-06 | 1(Win) | true |
| simdjson (ondemand) | 7091.19 | 0.0307925 | 845.821ms | 9739 | 640 | 104.102 | 1309.77 | 0.0540702 | 0.748326 | 3.502 | 0.379916 | 0.00052832 | 9.46581e-06 | 4.81312e-07 | 2(Loss) | true |
