
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1941.91 | 0.107347 | 236.06ms | 3223 | 320 | 923.819 | 1582.82 | 0.661203 | 1(Win) | true |
| Jsonifier (two-stage) | 1253.22 | 0.446059 | 307.572ms | 3223 | 1280 | 153202 | 2452.65 | 0.46376 | 2(Loss) | true |
| Glaze | 991.987 | 0.719037 | 354.316ms | 3223 | 640 | 317681 | 3098.52 | 0.11942 | 3(Loss) | true |
| simdjson (ondemand) | 815.002 | 0.121537 | 428.051ms | 3223 | 4890 | 102737 | 3771.39 | 0.0238753 | 4(Loss) | true |
