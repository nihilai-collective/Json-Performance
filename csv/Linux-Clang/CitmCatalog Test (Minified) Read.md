
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1251.37 | 0.131075 | 9949.06ms | 500299 | 1280 | 3.19694e+08 | 381280 | 0.143732 | 4.03438 | 17.9396 | 3.23276 | 0.0161853 | 0.0109512 | 0.00014747 | 1(Win) | true |
| simdjson (ondemand) | 1126.2 | 0.185803 | 5512.92ms | 500299 | 40 | 2.47851e+07 | 423656 | 0.140273 | 4.47394 | 18.6294 | 2.99423 | 0.0213924 | 0.0178104 | 6.30123e-05 | 2(Loss) | true |
