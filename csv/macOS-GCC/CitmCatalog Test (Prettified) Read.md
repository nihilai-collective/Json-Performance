
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2764.49 | 0.157529 | 5135.53ms | 1151920 | 640 | 2.50794e+08 | 397382 | 0.208933 | 1(Win) | true |
| Jsonifier (two-stage) | 2405.97 | 0.197752 | 6047.74ms | 1151920 | 640 | 5.21781e+08 | 456596 | 0.372035 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2041.74 | 0.342608 | 7342.77ms | 1151920 | 40 | 1.35924e+08 | 538048 | 0.331162 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2037.33 | 0.37931 | 6951.68ms | 1151920 | 80 | 3.34656e+08 | 539213 | 0.0106811 | 3(Tie) | true |
| Glaze | 1831.22 | 0.141884 | 7730.46ms | 1151920 | 640 | 4.63674e+08 | 599904 | 0.341349 | 5(Loss) | true |
