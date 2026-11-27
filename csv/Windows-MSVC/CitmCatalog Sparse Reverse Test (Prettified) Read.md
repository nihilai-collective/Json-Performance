
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5508.01 | 0.172321 | 5133.35ms | 1151920 | 320 | 3.77992e+07 | 199447 | 0.169347 | 0.551707 | 1(Win) | true |
| simdjson (ondemand) | 4697.43 | 0.22546 | 5967.05ms | 1151920 | 30 | 8.34033e+06 | 233863 | 0.0527652 | 0.646934 | 2(Loss) | true |
