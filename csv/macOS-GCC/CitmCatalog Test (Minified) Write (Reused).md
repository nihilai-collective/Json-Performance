
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7844.62 | 0.693488 | 6547.28ms | 500299 | 320 | 5.69304e+07 | 60821.6 | 0.919903 | 1(Win) | true |
| simdjson (reflection) | 6806.62 | 0.632038 | 7451.38ms | 500299 | 640 | 1.25621e+08 | 70096.8 | 0.107165 | 2(Loss) | true |
| Glaze | 1691.71 | 0.550014 | 6780.1ms | 500299 | 30 | 7.21897e+07 | 282035 | 0.129933 | 3(Loss) | true |
