
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9469.73 | 2.07171 | 34.6092ms | 3223 | 4890 | 221113 | 324.581 | 0.334089 | 1(Win) | true |
| simdjson (reflection) | 8157.36 | 3.62594 | 41.002ms | 3223 | 1280 | 238932 | 376.8 | 1.15425 | 2(Loss) | true |
| Glaze | 2076.82 | 0.731919 | 150.032ms | 3223 | 2560 | 300393 | 1480 | 0.31178 | 3(Loss) | true |
