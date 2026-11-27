
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18347.8 | 0.231894 | 2597.51ms | 500299 | 2560 | 9.30916e+06 | 26004.4 | 0.324009 | 0.134766 | 1(Win) | true |
| simdjson (stage-1) | 16359.7 | 0.209426 | 2953.25ms | 500299 | 2560 | 9.55024e+06 | 29164.6 | 0.13855 | 0.151164 | 2(Loss) | true |
