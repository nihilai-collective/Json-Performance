
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3346.15 | 0.180177 | 7452.4ms | 500299 | 1280 | 8.44848e+07 | 142588 | 1.11953 | 1(Win) | true |
| simdjson (ondemand) | 3160.75 | 0.0637145 | 7831.56ms | 500299 | 1280 | 1.18404e+07 | 150952 | 0.107832 | 2(Loss) | true |
