
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8008.1 | 0.59635 | 6398.05ms | 500299 | 320 | 4.03974e+07 | 59580 | 0.660936 | 1(Win) | true |
| simdjson (reflection) | 7310.16 | 0.331608 | 6667.52ms | 500299 | 640 | 2.99804e+07 | 65268.4 | 0.463619 | 2(Loss) | true |
| Glaze | 1815.93 | 0.517059 | 6204.92ms | 500299 | 160 | 2.95298e+08 | 262742 | 0.40722 | 3(Loss) | true |
