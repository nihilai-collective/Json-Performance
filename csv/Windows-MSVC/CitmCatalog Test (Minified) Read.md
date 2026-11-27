
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1484.86 | 0.301911 | 8412.23ms | 500299 | 40 | 3.7645e+07 | 321325 | 0.0212616 | 1.66723 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.49 | 0.277407 | 5266.21ms | 500299 | 30 | 3.61052e+07 | 395463 | 0.30001 | 2.05191 | 2(Loss) | true |
| Glaze | 672.882 | 0.286165 | 9252.41ms | 500299 | 160 | 6.58771e+08 | 709073 | 0.212612 | 3.67919 | 3(Loss) | true |
| simdjson (ondemand) | 637.813 | 0.322056 | 9640.23ms | 500299 | 30 | 1.74123e+08 | 748060 | 0.969572 | 3.88154 | 4(Loss) | true |
