
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3711.87 | 0.645251 | 9421.51ms | 1439562 | 30 | 1.70865e+08 | 369860 | 0.460846 | 0.666781 | 1(Win) | true |
| Glaze | 1971.07 | 0.125753 | 8902.17ms | 1439584 | 320 | 2.45505e+08 | 696522 | 0.28332 | 1.25583 | 2(Loss) | true |
