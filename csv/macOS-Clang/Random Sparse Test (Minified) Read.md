
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1820.73 | 0.251459 | 5458.65ms | 409725 | 320 | 9.31918e+07 | 214608 | 0.13139 | 1(Win) | true |
| simdjson (ondemand) | 1299.1 | 0.107281 | 7730.65ms | 409725 | 640 | 6.66384e+07 | 300781 | 0.19519 | 2(Loss) | true |
