
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 564.418 | 0.129901 | 879.977ms | 5092 | 160 | 19985.8 | 8603.75 | 0.534682 | 5.37408 | 1(Win) | true |
| simdjson (ondemand) | 545.745 | 0.231657 | 901.404ms | 5092 | 160 | 67983.9 | 8898.12 | 0.387816 | 5.55855 | 2(Loss) | true |
