
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5563.41 | 0.0685237 | 9421.79ms | 500299 | 160 | 552560 | 85760.8 | 0.0952098 | 0.925476 | 4.93347 | 0.762054 | 0.000935253 | 2.33236e-05 | 2.16745e-05 | 1(Win) | true |
| simdjson (ondemand) | 4986.06 | 0.10669 | 5361.14ms | 500299 | 80 | 833834 | 95691.3 | 0.0394392 | 1.02596 | 5.6139 | 0.720413 | 0.0010403 | 1.47412e-05 | 8.24507e-07 | 2(Loss) | true |
