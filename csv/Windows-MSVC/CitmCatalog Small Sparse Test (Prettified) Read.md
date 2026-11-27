
----
### CitmCatalog Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6739.47 | 0.186782 | 139.961ms | 9739 | 1280 | 8481.24 | 1378.12 | 0.0566572 | 0.445148 | 1(Win) | true |
| simdjson (ondemand) | 5448.91 | 0.288313 | 170.126ms | 9739 | 640 | 15456.7 | 1704.53 | 0.0458127 | 0.551447 | 2(Loss) | true |
