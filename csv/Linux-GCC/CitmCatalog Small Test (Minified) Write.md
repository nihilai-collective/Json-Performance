
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7730.61 | 0.278298 | 43.9805ms | 3223 | 30 | 36.731 | 397.6 | 0.342552 | 0.298459 | 1(Win) | true |
| simdjson (reflection) | 7654.93 | 0.158466 | 43.8629ms | 3223 | 160 | 64.7789 | 401.531 | 0.295054 | 0.30282 | 2(Loss) | true |
| Glaze | 2396.65 | 0.115946 | 127.627ms | 3223 | 160 | 353.786 | 1282.49 | 0.37715 | 1.01122 | 3(Loss) | true |
