
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2683.86 | 0.142395 | 181.571ms | 5092 | 1280 | 8496.87 | 1809.38 | 0.0691324 | 1.12074 | 1(Win) | true |
| simdjson (ondemand) | 2458.42 | 0.188491 | 199.453ms | 5092 | 4890 | 67788.1 | 1975.3 | 0.227708 | 1.22465 | 2(Loss) | true |
