
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.509 | 0.166643 | 8479.34ms | 500299 | 640 | 7.94723e+08 | 668699 | 0.261825 | 4.25933 | 1(Win) | true |
| simdjson (ondemand) | 605.425 | 0.150516 | 10030.5ms | 500299 | 320 | 4.50251e+08 | 788079 | 0.250614 | 5.01996 | 2(Loss) | true |
