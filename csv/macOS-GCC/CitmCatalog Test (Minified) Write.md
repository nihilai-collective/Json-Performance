
----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8773.99 | 0.143976 | 5659.14ms | 500299 | 320 | 1.96154e+06 | 54379.2 | 0.0264877 | 1(Win) | true |
| simdjson (reflection) | 7810.82 | 0.435032 | 5847.27ms | 500299 | 640 | 4.51948e+07 | 61084.8 | 0.209107 | 2(Loss) | true |
| Glaze | 2078.54 | 0.348034 | 5964.27ms | 500299 | 320 | 2.04237e+08 | 229546 | 0.515305 | 3(Loss) | true |
