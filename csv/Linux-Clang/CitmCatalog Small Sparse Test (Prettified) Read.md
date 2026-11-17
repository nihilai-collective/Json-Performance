
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7470.13 | 0.0304621 | 839.084ms | 9739 | 4890 | 701.457 | 1243.33 | 0.00779231 | 0.711996 | 3.2068 | 0.390492 | 0.000571501 | 7.70625e-06 | 3.14969e-07 | 1(Win) | true |
| simdjson (ondemand) | 7429.73 | 0.0327625 | 836.521ms | 9739 | 4890 | 820.251 | 1250.09 | 0.0889913 | 0.715532 | 3.3486 | 0.373961 | 0.00032003 | 1.39846e-05 | 3.92662e-06 | 2(Loss) | true |
