
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10748.1 | 0.0705662 | 31.245ms | 3223 | 640 | 26.0636 | 285.977 | 0.16201 | 0.209683 | 1(Win) | true |
| Glaze | 2744.25 | 0.158275 | 112.321ms | 3223 | 80 | 251.415 | 1120.05 | 0.327037 | 0.882284 | 2(Loss) | true |
