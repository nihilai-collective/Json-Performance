
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7962.61 | 0.286309 | 42.1594ms | 3223 | 1280 | 1563.47 | 386.016 | 0.101297 | 0.288254 | 1(Win) | true |
| Glaze | 2315.4 | 0.378431 | 132.286ms | 3223 | 80 | 2018.99 | 1327.5 | 0.375235 | 1.04972 | 2(Loss) | true |
