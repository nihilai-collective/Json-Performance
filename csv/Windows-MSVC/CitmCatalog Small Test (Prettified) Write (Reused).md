
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8402.02 | 0.672475 | 83.8901ms | 6938 | 40 | 1121.79 | 787.5 | 0.105932 | 0.285356 | 1(Win) | true |
| Glaze | 4290.85 | 0.274427 | 158.727ms | 6960 | 4890 | 88124 | 1546.91 | 0.408085 | 0.566368 | 2(Loss) | true |
