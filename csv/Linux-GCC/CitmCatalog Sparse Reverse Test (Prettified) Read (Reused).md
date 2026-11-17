
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5709.83 | 0.0600298 | 5116.81ms | 1151920 | 640 | 8.53715e+06 | 192397 | 0.0756316 | 0.898742 | 4.81196 | 0.789576 | 0.0011616 | 0.00722829 | 1.11499e-06 | 1(Win) | true |
| simdjson (ondemand) | 5663.33 | 0.0336646 | 5166.22ms | 1151920 | 160 | 682288 | 193977 | 0.0145099 | 0.908919 | 5.17857 | 0.7823 | 0.00141068 | 0.00961335 | 2.51211e-06 | 2(Loss) | true |
