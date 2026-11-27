
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.175 | 0.724596 | 9684.61ms | 4525119 | 80 | 1.64696e+11 | 6.26182e+06 | 0.148478 | 4.40982 | 1(Win) | true |
| simdjson (ondemand) | 553.088 | 0.78612 | 5612.52ms | 4525119 | 30 | 1.12868e+11 | 7.80254e+06 | 0.137884 | 5.49489 | 2(Loss) | true |
