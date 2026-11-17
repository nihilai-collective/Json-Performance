
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14900.1 | 0.237319 | 5113.87ms | 1439562 | 40 | 1.91254e+06 | 92138.7 | 0.288721 | 0.334344 | 1.34878 | 0.257958 | 0.000807694 | 0.0179202 | 6.85973e-06 | 1(Win) | true |
| Glaze | 7093.37 | 0.10934 | 5165.48ms | 1439584 | 320 | 1.43309e+07 | 193546 | 0.0556815 | 0.712282 | 3.06771 | 0.527269 | 0.00101149 | 0.0182938 | 1.57967e-05 | 2(Loss) | true |
