
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16135.2 | 1.7236 | 43.5981ms | 6938 | 4890 | 244286 | 410.071 | 0.395636 | 1(Win) | true |
| Glaze | 2669.11 | 0.31224 | 254.486ms | 6960 | 4890 | 294829 | 2486.81 | 0.376081 | 2(Loss) | true |
| simdjson (reflection) | 346.949 | 0.10577 | 1921.03ms | 6938 | 1280 | 520802 | 19070.8 | 0.00419507 | 3(Loss) | true |
