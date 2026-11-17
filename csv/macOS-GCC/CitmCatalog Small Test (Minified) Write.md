
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6842.59 | 2.19995 | 46.2349ms | 3223 | 2560 | 250003 | 449.2 | 0.62724 | 1(Win) | true |
| simdjson (reflection) | 5604.84 | 4.2464 | 51.3879ms | 3223 | 640 | 347070 | 548.4 | 1.40533 | 2(Loss) | true |
| Glaze | 1541.47 | 0.753891 | 194.672ms | 3223 | 1280 | 289252 | 1994 | 0.0601443 | 3(Loss) | true |
