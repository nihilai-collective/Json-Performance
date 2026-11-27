
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2295.16 | 0.0826122 | 5518.89ms | 500299 | 640 | 1.88756e+07 | 207882 | 0.012601 | 2.21009 | 9.84826 | 1.92019 | 0.0107812 | 0.0106245 | 3.32145e-05 | 1(Win) | true |
| Glaze | 1788.5 | 0.0546439 | 7039.91ms | 500299 | 1280 | 2.72005e+07 | 266773 | 0.318337 | 2.83799 | 12.5358 | 2.36605 | 0.014151 | 0.00549814 | 5.72252e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1685.35 | 0.0726767 | 7427.28ms | 500299 | 640 | 2.70925e+07 | 283100 | 0.0654521 | 2.9934 | 13.4126 | 2.37637 | 0.0147299 | 0.0450917 | 4.89457e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1114.2 | 0.0693797 | 5549.19ms | 500299 | 640 | 5.64905e+07 | 428219 | 0.342354 | 4.53866 | 19.193 | 2.85368 | 0.0160475 | 0.0478628 | 0.000155726 | 4(Loss) | true |
