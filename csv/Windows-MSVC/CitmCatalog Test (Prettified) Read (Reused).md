
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2621.05 | 0.251451 | 5739.24ms | 1151920 | 160 | 1.77714e+08 | 419129 | 1.19086 | 0.944502 | 1(Win) | true |
| Jsonifier | 2329.03 | 0.448038 | 6592.15ms | 1151920 | 320 | 1.42914e+09 | 471680 | 0.358527 | 1.06295 | 2(Loss) | true |
| Glaze | 1456.27 | 0.475095 | 10175.7ms | 1151920 | 640 | 8.22063e+09 | 754366 | 0.226863 | 1.70003 | 3(Loss) | true |
| simdjson (ondemand) | 1141.91 | 0.280906 | 6296.95ms | 1151920 | 30 | 2.19091e+08 | 962033 | 0.086003 | 2.16804 | 4(Loss) | true |
