
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2094.09 | 0.270498 | 353.069ms | 5839 | 2560 | 132450 | 2659.15 | 2.11523 | 1(Win) | true |
| Jsonifier (two-stage) | 1969.53 | 0.386804 | 349.622ms | 5839 | 1280 | 153088 | 2827.32 | 0.998889 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1437.03 | 0.663165 | 460.308ms | 5839 | 40 | 26414.7 | 3875 | 0.360001 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1427.35 | 0.816156 | 482.706ms | 5839 | 160 | 162211 | 3901.28 | 0.420045 | 3(Tie) | true |
