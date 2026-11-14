
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16617.3 | 0.328924 | 8339.28ms | 1439562 | 2560 | 1.89047e+08 | 82617 | 0.552805 | 1(Win) | true |
| Glaze | 3634.28 | 0.208848 | 5036.4ms | 1439584 | 30 | 1.86732e+07 | 377762 | 0.799217 | 2(Loss) | true |
| simdjson (reflection) | 306.994 | 0.711992 | 6947.17ms | 1439562 | 80 | 8.1104e+10 | 4.47199e+06 | 0.0632159 | 3(Loss) | true |
