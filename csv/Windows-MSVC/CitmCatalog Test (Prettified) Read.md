
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1480.28 | 0.114185 | 9413.8ms | 1151920 | 640 | 4.5958e+08 | 742129 | 0.109215 | 2.05298 | 1(Win) | true |
| simdjson (ondemand) | 1401.68 | 0.108344 | 9964.48ms | 1151920 | 640 | 4.61469e+08 | 783745 | 0.105094 | 2.16813 | 2(Loss) | true |
