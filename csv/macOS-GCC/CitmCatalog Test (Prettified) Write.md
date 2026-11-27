
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17201.4 | 0.174235 | 8189.72ms | 1439562 | 4890 | 9.45615e+07 | 79811.6 | 1.02125 | 1(Win) | true |
| Glaze | 3573.21 | 0.256445 | 10048.6ms | 1439584 | 640 | 6.21332e+08 | 384218 | 1.00209 | 2(Loss) | true |
| simdjson (reflection) | 318.438 | 1.18457 | 6776.09ms | 1439562 | 30 | 7.82453e+10 | 4.31128e+06 | 2.48616 | 3(Loss) | true |
