
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1642.63 | 0.294985 | 399.777ms | 5839 | 40 | 4000 | 3390 | 0.394867 | 1.49457 | 1(Win) | true |
| Jsonifier | 1425.39 | 0.170648 | 466.464ms | 5839 | 30 | 1333.33 | 3906.67 | 0.25663 | 1.72574 | 2(Loss) | true |
| Glaze | 953.332 | 0.324289 | 660.167ms | 5839 | 1280 | 459264 | 5841.09 | 0.0615632 | 2.5848 | 3(Loss) | true |
| simdjson (ondemand) | 933.131 | 0.176031 | 688.485ms | 5839 | 4890 | 539611 | 5967.55 | 0.0826621 | 2.64153 | 4(Loss) | true |
