
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8688.36 | 0.199535 | 6525.28ms | 1151920 | 40 | 2.54605e+06 | 126440 | 0.0605981 | 0.349734 | 1(Win) | true |
| simdjson (ondemand) | 7152.56 | 0.316 | 7899.99ms | 1151920 | 640 | 1.50757e+08 | 153589 | 0.592417 | 0.424837 | 2(Loss) | true |
