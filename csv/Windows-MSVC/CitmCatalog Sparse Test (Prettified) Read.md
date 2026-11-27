
----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8474.6 | 0.0979856 | 6638.66ms | 1151920 | 2560 | 4.13021e+07 | 129629 | 0.133793 | 0.358546 | 1(Win) | true |
| simdjson (ondemand) | 7017.93 | 0.185548 | 8041.82ms | 1151920 | 320 | 2.69953e+07 | 156536 | 0.244155 | 0.432592 | 2(Loss) | true |
