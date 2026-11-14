
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17474.6 | 0.255099 | 7837.33ms | 1439562 | 2560 | 1.02826e+08 | 78563.8 | 0.627625 | 1(Win) | true |
| Glaze | 4209.69 | 0.698143 | 8542.61ms | 1439584 | 30 | 1.55519e+08 | 326127 | 0.438885 | 2(Loss) | true |
| simdjson (reflection) | 324.646 | 0.396414 | 6637.64ms | 1439562 | 80 | 2.24816e+10 | 4.22883e+06 | 1.31453 | 3(Loss) | true |
