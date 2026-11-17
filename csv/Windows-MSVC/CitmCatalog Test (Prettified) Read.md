
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1391.08 | 0.136924 | 5031.84ms | 1151920 | 80 | 9.35376e+07 | 789712 | 0.533083 | 1.7797 | 1(Win) | true |
| simdjson (ondemand) | 1211.19 | 0.23044 | 5826.42ms | 1151920 | 30 | 1.31056e+08 | 907003 | 0.0665637 | 2.04406 | 2(Loss) | true |
