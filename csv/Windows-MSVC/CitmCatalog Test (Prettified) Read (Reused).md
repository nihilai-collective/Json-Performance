
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2857.73 | 0.108034 | 5436.19ms | 1151920 | 640 | 1.10383e+08 | 384416 | 0.101958 | 0.866274 | 1(Win) | true |
| Jsonifier | 2415.61 | 0.377936 | 6398.19ms | 1151920 | 30 | 8.86234e+07 | 454773 | 0.012462 | 1.02488 | 2(Loss) | true |
| Glaze | 1590.86 | 0.152012 | 5132.09ms | 1151920 | 160 | 1.76301e+08 | 690542 | 0.353 | 1.55622 | 3(Loss) | true |
| simdjson (ondemand) | 1229.93 | 0.110393 | 5996.9ms | 1151920 | 160 | 1.55557e+08 | 893189 | 0.139264 | 2.01288 | 4(Loss) | true |
