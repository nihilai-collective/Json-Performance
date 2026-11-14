
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15354.9 | 0.218465 | 5180.47ms | 1439562 | 30 | 1.14459e+06 | 89409.4 | 0.0264397 | 0.329095 | 1.34917 | 0.258045 | 0.000855978 | 0.0184824 | 1.28743e-05 | 1(Win) | true |
| Glaze | 5195.67 | 0.645879 | 7095.98ms | 1439584 | 320 | 9.32061e+08 | 264238 | 0.640209 | 0.967654 | 3.07289 | 0.528478 | 0.0010004 | 0.063341 | 2.35094e-05 | 2(Loss) | true |
