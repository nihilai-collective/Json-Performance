
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1643.86 | 0.861952 | 9618.32ms | 1151920 | 320 | 1.06178e+10 | 668280 | 1.04903 | 1(Win) | true |
| simdjson (ondemand) | 1524.5 | 1.77322 | 5112.84ms | 1151920 | 40 | 6.53095e+09 | 720602 | 3.55809 | 2(Loss) | true |
