
----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8762.98 | 0.432304 | 5555.85ms | 500299 | 160 | 8.86452e+06 | 54447.5 | 0.251901 | 0.282349 | 1(Win) | true |
| Glaze | 3184.93 | 0.148688 | 7817.24ms | 500299 | 1280 | 6.35074e+07 | 149806 | 0.543638 | 0.777168 | 2(Loss) | true |
