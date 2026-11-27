
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1553.54 | 0.174353 | 8959.22ms | 1151920 | 320 | 4.86418e+08 | 707133 | 0.00932376 | 1.95618 | 1(Win) | true |
| simdjson (ondemand) | 1310.22 | 0.370826 | 5313.85ms | 1151920 | 40 | 3.86683e+08 | 838450 | 0.0532445 | 2.31959 | 2(Loss) | true |
