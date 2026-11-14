
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8900.21 | 0.0661894 | 6737.05ms | 1151920 | 30 | 200237 | 123430 | 0.0324234 | 0.578639 | 2.87229 | 0.333502 | 0.000580596 | 0.00445372 | 2.60435e-07 | 1(Win) | true |
| simdjson (ondemand) | 8093.52 | 0.0389669 | 7340.09ms | 1151920 | 320 | 895185 | 135733 | 0.0130259 | 0.634854 | 3.20449 | 0.344854 | 0.000864163 | 0.0046825 | 7.32473e-08 | 2(Loss) | true |
