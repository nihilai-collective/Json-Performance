
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1392.94 | 0.0831636 | 8987.29ms | 500299 | 1280 | 1.03865e+08 | 342528 | 0.1369 | 1.77716 | 1(Win) | true |
| Jsonifier (two-stage) | 1139.21 | 0.349819 | 5479.7ms | 500299 | 40 | 8.5861e+07 | 418818 | 0.94096 | 2.17309 | 2(Loss) | true |
| Glaze | 684.727 | 0.45824 | 9046.1ms | 500299 | 30 | 3.05867e+08 | 696807 | 0.0478602 | 3.61557 | 3(Loss) | true |
| simdjson (ondemand) | 599.839 | 0.188497 | 5139.71ms | 500299 | 80 | 1.79841e+08 | 795418 | 0.0442967 | 4.12728 | 4(Loss) | true |
