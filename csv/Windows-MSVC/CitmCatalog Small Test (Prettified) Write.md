
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7720.36 | 0.336849 | 90.9975ms | 6938 | 640 | 5333.9 | 857.031 | 0.272727 | 0.311351 | 1(Win) | true |
| Glaze | 3670.89 | 0.396639 | 185.093ms | 6960 | 2560 | 131676 | 1808.16 | 0.0712404 | 0.664236 | 2(Loss) | true |
