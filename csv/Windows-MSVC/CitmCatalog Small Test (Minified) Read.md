
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 776.839 | 0.313273 | 418.049ms | 3223 | 30 | 4609.2 | 3956.67 | 0 | 3.16172 | 1(Win) | true |
| Jsonifier (two-stage) | 680.114 | 0.219783 | 462.742ms | 3223 | 160 | 15785.8 | 4519.38 | 0.0968992 | 3.61392 | 2(Loss) | true |
| Glaze | 461.211 | 0.193843 | 688.741ms | 3223 | 4890 | 816079 | 6664.4 | 0.0289724 | 5.34534 | 3(Loss) | true |
| simdjson (ondemand) | 422.014 | 0.178509 | 738.938ms | 3223 | 4890 | 826605 | 7283.39 | 0.0504404 | 5.84285 | 4(Loss) | true |
