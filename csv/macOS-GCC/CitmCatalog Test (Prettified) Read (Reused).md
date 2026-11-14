
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3142.71 | 0.334522 | 5156.05ms | 1151920 | 320 | 4.37556e+08 | 349557 | 0.0187631 | 1(Win) | true |
| Jsonifier (two-stage) | 2718.62 | 0.342735 | 5763.52ms | 1151920 | 320 | 6.13783e+08 | 404086 | 1.14743 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2217.98 | 0.239767 | 7263.65ms | 1151920 | 640 | 9.02588e+08 | 495297 | 0.861488 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2216.03 | 0.235347 | 6836.92ms | 1151920 | 160 | 2.17786e+08 | 495731 | 0.00258198 | 3(Tie) | true |
| Glaze | 2017.77 | 0.149542 | 7515.5ms | 1151920 | 320 | 2.12118e+08 | 544442 | 0.202008 | 5(Loss) | true |
