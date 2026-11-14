
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1635.98 | 0.11633 | 7426.7ms | 500299 | 640 | 7.3666e+07 | 291642 | 0.0312445 | 1.8577 | 1(Win) | true |
| Jsonifier (two-stage) | 1309.47 | 0.1363 | 9402.54ms | 500299 | 40 | 9.86548e+06 | 364362 | 0.02997 | 2.32084 | 2(Loss) | true |
| Glaze | 883.56 | 0.0902797 | 6860.64ms | 500299 | 320 | 7.60532e+07 | 540000 | 0.222882 | 3.43977 | 3(Loss) | true |
| simdjson (ondemand) | 629.32 | 0.0735554 | 9640ms | 500299 | 640 | 1.99033e+08 | 758155 | 0.0209346 | 4.82927 | 4(Loss) | true |
