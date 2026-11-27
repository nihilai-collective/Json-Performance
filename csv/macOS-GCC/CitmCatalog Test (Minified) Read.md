
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2082.62 | 0.0868233 | 5980.85ms | 500299 | 640 | 2.53216e+07 | 229097 | 0.0289918 | 1(Win) | true |
| Jsonifier (two-stage) | 1327.34 | 0.261477 | 5038.71ms | 500299 | 30 | 2.65025e+07 | 359458 | 0.0569422 | 2(Loss) | true |
| Glaze | 1091 | 0.97765 | 5155.93ms | 500299 | 40 | 7.31198e+08 | 437325 | 1.02107 | 3(Loss) | true |
| simdjson (reflection) | 1049.55 | 0.839845 | 6081.92ms | 500299 | 160 | 2.33224e+09 | 454598 | 2.76253 | 4(Loss) | true |
| simdjson (ondemand) | 915.506 | 0.638212 | 6320.7ms | 500299 | 160 | 1.77006e+09 | 521157 | 0.222699 | 5(Loss) | true |
