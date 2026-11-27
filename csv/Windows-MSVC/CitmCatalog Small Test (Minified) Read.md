
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.333 | 0.355255 | 431.581ms | 3223 | 40 | 8820.51 | 4180 | 0 | 3.32683 | 1(Win) | true |
| Jsonifier (two-stage) | 638.579 | 0.258479 | 492.796ms | 3223 | 30 | 4643.68 | 4813.33 | 0 | 3.82645 | 2(Loss) | true |
| Glaze | 469.027 | 0.228257 | 672.911ms | 3223 | 30 | 6712.64 | 6553.33 | 0.0508388 | 5.23037 | 3(Loss) | true |
| simdjson (ondemand) | 446.616 | 0.220806 | 737.051ms | 3223 | 2560 | 591171 | 6882.19 | 0.114784 | 5.52003 | 4(Loss) | true |
