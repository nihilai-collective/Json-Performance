
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 9453.17 | 0.275409 | 5079.95ms | 500299 | 2560 | 4.94654e+07 | 50472.2 | 0.0965261 | 0.321238 | 1(Win) | true |
| simdjson (stage-1) | 8535.66 | 0.0843846 | 5820.83ms | 500299 | 320 | 711969 | 55897.5 | 0.611206 | 0.355797 | 2(Loss) | true |
