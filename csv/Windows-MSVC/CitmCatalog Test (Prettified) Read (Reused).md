
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1600.39 | 0.0689973 | 9248.19ms | 1151920 | 640 | 1.43562e+08 | 686432 | 0.0109021 | 1.89893 | 1(Win) | true |
| simdjson (ondemand) | 1495.48 | 0.0937583 | 9826.47ms | 1151920 | 640 | 3.03586e+08 | 734584 | 0.166463 | 2.03218 | 2(Loss) | true |
