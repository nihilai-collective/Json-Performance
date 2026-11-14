
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17341.8 | 1.82825 | 40.9001ms | 6938 | 4890 | 237936 | 381.539 | 1.69042 | 1(Win) | true |
| Glaze | 2755.32 | 0.582191 | 250.919ms | 6960 | 1280 | 251777 | 2409 | 0.157991 | 2(Loss) | true |
| simdjson (reflection) | 315.052 | 0.40541 | 2065.5ms | 6938 | 320 | 2.31976e+06 | 21001.6 | 0.432375 | 3(Loss) | true |
