
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 447.858 | 0.817275 | 6817.88ms | 500299 | 320 | 2.42586e+10 | 1.06534e+06 | 0.304698 | 1(Win) | true |
| simdjson (ondemand) | 256.094 | 0.983703 | 5138.56ms | 500299 | 40 | 1.34354e+10 | 1.86308e+06 | 3.40068 | 2(Loss) | true |
