
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18240.8 | 0.419033 | 7740.19ms | 1439562 | 80 | 7.95723e+06 | 75264 | 0.213038 | 1(Win) | true |
| Glaze | 3406.75 | 0.41944 | 5344.57ms | 1439584 | 640 | 1.82858e+09 | 402993 | 0.739133 | 2(Loss) | true |
| simdjson (reflection) | 299.97 | 1.89849 | 7222.07ms | 1439562 | 30 | 2.26488e+11 | 4.5767e+06 | 2.72333 | 3(Loss) | true |
