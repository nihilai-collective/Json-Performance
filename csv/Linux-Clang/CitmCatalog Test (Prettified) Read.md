
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3814.21 | 0.136955 | 7376.45ms | 1151920 | 320 | 4.97903e+07 | 288017 | 0.0328768 | 0.649003 | 1(Win) | true |
| Jsonifier (two-stage) | 3563.08 | 0.25993 | 7738.91ms | 1151920 | 640 | 4.11042e+08 | 308316 | 0.403131 | 0.69473 | 2(Loss) | true |
| Glaze | 2439.8 | 0.0885305 | 5756.34ms | 1151920 | 320 | 5.08479e+07 | 450266 | 0.268087 | 1.01467 | 3(Loss) | true |
| simdjson (ondemand) | 2219.31 | 0.14209 | 6208.1ms | 1151920 | 80 | 3.95754e+07 | 495000 | 0.012501 | 1.11546 | 4(Loss) | true |
