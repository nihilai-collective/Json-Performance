
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5118.5 | 0.05474 | 910.226ms | 9739 | 4890 | 4824.61 | 1814.56 | 0.0783191 | 1.00977 | 4.93675 | 0.710237 | 0.000943081 | 2.27618e-05 | 8.79814e-06 | 1(Win) | true |
| Jsonifier (generic) | 4864.91 | 0.051164 | 919.418ms | 9739 | 2560 | 2442.57 | 1909.15 | 0.0294343 | 1.05987 | 4.80594 | 0.756135 | 0.00125498 | 1.21932e-05 | 2.92798e-06 | 2(Loss) | true |
