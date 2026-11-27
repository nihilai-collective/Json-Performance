
----
### CitmCatalog Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5340.35 | 0.115383 | 177.244ms | 9739 | 2560 | 10308.8 | 1739.18 | 0.271033 | 0.563301 | 1(Win) | true |
| simdjson (ondemand) | 4429.12 | 0.110331 | 213.088ms | 9739 | 2560 | 13703.3 | 2096.99 | 0.0204949 | 0.67986 | 2(Loss) | true |
