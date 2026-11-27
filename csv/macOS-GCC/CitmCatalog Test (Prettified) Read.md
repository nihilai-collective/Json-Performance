
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2757.03 | 0.475289 | 9762.85ms | 1151920 | 160 | 5.73848e+08 | 398456 | 1.27491 | 1(Win) | true |
| Jsonifier (two-stage) | 2658.96 | 0.141367 | 5285.95ms | 1151920 | 80 | 2.72901e+07 | 413152 | 0.00619665 | 2(Loss) | true |
| simdjson (reflection) | 2260.51 | 0.154222 | 6618.72ms | 1151920 | 40 | 2.24689e+07 | 485978 | 0.0517726 | 3(Loss) | true |
| simdjson (ondemand) | 2125.46 | 0.22863 | 6404.49ms | 1151920 | 640 | 8.93683e+08 | 516856 | 1.30105 | 4(Loss) | true |
| Glaze | 1623.42 | 0.383828 | 8328.71ms | 1151920 | 320 | 2.15876e+09 | 676691 | 0.368552 | 5(Loss) | true |
