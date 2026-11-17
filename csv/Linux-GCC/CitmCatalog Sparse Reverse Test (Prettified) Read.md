
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5699.67 | 0.0602181 | 5196.34ms | 1151920 | 30 | 404129 | 192740 | 0.0522911 | 0.90319 | 4.82304 | 0.792308 | 0.00121692 | 0.00790689 | 3.44642e-05 | 1(Win) | true |
| simdjson (ondemand) | 5621.1 | 0.0469544 | 5222.99ms | 1151920 | 160 | 1.34733e+06 | 195434 | 0.0855693 | 0.914478 | 5.18965 | 0.785032 | 0.00148591 | 0.0099486 | 1.05259e-06 | 2(Loss) | true |
