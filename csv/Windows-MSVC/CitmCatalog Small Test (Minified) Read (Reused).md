
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 654.988 | 0.0657394 | 835.37ms | 5092 | 4890 | 116164 | 7414.05 | 0.123842 | 4.62577 | 1(Win) | true |
| Jsonifier (generic) | 599.427 | 0.0656801 | 908.576ms | 5092 | 4890 | 138446 | 8101.25 | 0.0982993 | 5.05653 | 2(Loss) | true |
