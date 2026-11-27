
----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8695.37 | 0.160122 | 5471.67ms | 500299 | 1280 | 9.88089e+06 | 54870.9 | 0.285143 | 0.284551 | 1(Win) | true |
| Glaze | 3312.21 | 0.0887427 | 7421.82ms | 500299 | 1280 | 2.0917e+07 | 144050 | 0.122745 | 0.747313 | 2(Loss) | true |
