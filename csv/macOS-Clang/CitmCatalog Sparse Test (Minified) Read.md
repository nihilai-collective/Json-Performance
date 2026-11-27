
----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3193.1 | 0.18611 | 7506.53ms | 500299 | 640 | 4.94942e+07 | 149423 | 1.52468 | 1(Win) | true |
| simdjson (ondemand) | 3016.52 | 0.0695507 | 8191.44ms | 500299 | 2560 | 3.09806e+07 | 158170 | 0.00389277 | 2(Loss) | true |
