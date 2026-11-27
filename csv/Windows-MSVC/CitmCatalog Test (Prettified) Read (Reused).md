
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2777.49 | 0.192416 | 5532.88ms | 1151920 | 320 | 1.85341e+08 | 395522 | 0.325628 | 0.891309 | 1(Win) | true |
| Jsonifier (two-stage) | 2763.33 | 0.162727 | 5761.15ms | 1151920 | 160 | 6.69601e+07 | 397548 | 0.26139 | 0.895859 | 2(Loss) | true |
| Glaze | 1434.91 | 0.294644 | 5106.7ms | 1151920 | 30 | 1.52655e+08 | 765590 | 0.168782 | 1.72533 | 3(Loss) | true |
| simdjson (ondemand) | 1328.63 | 0.101918 | 5479.3ms | 1151920 | 320 | 2.27242e+08 | 826833 | 0.333134 | 1.86334 | 4(Loss) | true |
