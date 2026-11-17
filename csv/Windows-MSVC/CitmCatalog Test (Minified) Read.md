
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1519.79 | 0.209248 | 8017.17ms | 500299 | 40 | 1.72614e+07 | 313940 | 0.139958 | 1.99976 | 1(Win) | true |
| Jsonifier (two-stage) | 1250.38 | 0.114022 | 9783.47ms | 500299 | 1280 | 2.42306e+08 | 381583 | 0.246531 | 2.4304 | 2(Loss) | true |
| Glaze | 821.285 | 0.143724 | 7385.62ms | 500299 | 160 | 1.11545e+08 | 580946 | 0.3262 | 3.70065 | 3(Loss) | true |
| simdjson (ondemand) | 540.675 | 0.314876 | 5602.74ms | 500299 | 30 | 2.31625e+08 | 882457 | 0.288885 | 5.62124 | 4(Loss) | true |
