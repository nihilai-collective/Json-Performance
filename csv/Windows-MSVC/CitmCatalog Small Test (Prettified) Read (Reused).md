
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1702.54 | 0.135325 | 391.69ms | 5839 | 1280 | 25075.3 | 3270.7 | 0.270646 | 1.77181 | 1(Win) | true |
| Jsonifier | 1482.46 | 0.176149 | 440.733ms | 5839 | 160 | 7004.72 | 3756.25 | 0.166667 | 2.03919 | 2(Loss) | true |
| Glaze | 1257.26 | 0.185346 | 505.471ms | 5839 | 640 | 43129 | 4429.06 | 0.190867 | 2.40701 | 3(Loss) | true |
| simdjson (ondemand) | 1247.15 | 0.105453 | 503.851ms | 5839 | 160 | 3547.17 | 4465 | 0.140174 | 2.42366 | 4(Loss) | true |
