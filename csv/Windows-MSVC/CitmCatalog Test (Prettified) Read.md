
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20592.2 | 0.233732 | 5279.91ms | 1151920 | 640 | 9.95073e+06 | 53348.1 | 0.204266 | 0.120164 | 1(Win) | true |
| simdjson (stage-1) | 19296.1 | 0.277835 | 5796.38ms | 1151920 | 320 | 8.00624e+06 | 56931.6 | 0.0871997 | 0.128228 | 2(Loss) | true |
