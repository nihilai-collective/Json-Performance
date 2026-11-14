
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 408.223 | 0.129631 | 1190.99ms | 5092 | 4890 | 1.1628e+06 | 11895.7 | 0.146862 | 7.43112 | 1(Win) | true |
| simdjson (ondemand) | 309.478 | 0.0707223 | 1573.93ms | 5092 | 4890 | 602196 | 15691.3 | 0.166686 | 9.80642 | 2(Loss) | true |
