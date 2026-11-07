
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 992.699 | 0.236369 | 387.434ms | 3223 | 4890 | 261923 | 3096.3 | 0.0141865 | 2.47265 | 1(Win) | true |
| Jsonifier (two-stage) | 857.227 | 0.181914 | 427.596ms | 3223 | 4890 | 208051 | 3585.62 | 0.342119 | 2.86629 | 2(Loss) | true |
| Glaze | 585.187 | 0.15224 | 600.556ms | 3223 | 40 | 2557.69 | 5252.5 | 0.268987 | 4.21154 | 3(Loss) | true |
| simdjson (ondemand) | 502.956 | 0.096516 | 696.185ms | 3223 | 80 | 2783.23 | 6111.25 | 0.142974 | 4.89435 | 4(Loss) | true |
