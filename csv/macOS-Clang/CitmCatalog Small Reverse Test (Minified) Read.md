
----
### CitmCatalog Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 522.748 | 0.0491854 | 946.157ms | 5092 | 80 | 1670.15 | 9289.58 | 0.0110351 | 1(Win) | true |
| simdjson (ondemand) | 294.389 | 0.271217 | 1748.11ms | 5092 | 320 | 640498 | 16495.6 | 0.434649 | 2(Loss) | true |
