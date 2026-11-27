
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 403.384 | 0.201954 | 1255.57ms | 5092 | 320 | 189145 | 12038.4 | 0.132213 | 7.51954 | 1(Win) | true |
| simdjson (ondemand) | 297.915 | 0.140486 | 1675.46ms | 5092 | 320 | 167806 | 16300.3 | 0.383866 | 10.1878 | 2(Loss) | true |
