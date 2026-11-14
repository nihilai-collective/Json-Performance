
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1213.23 | 0.116819 | 318.594ms | 3223 | 2560 | 22423.2 | 2533.48 | 0.0231225 | 2.48633 | 1(Win) | true |
| Jsonifier (two-stage) | 977.132 | 0.190189 | 383.76ms | 3223 | 1280 | 45813.5 | 3145.62 | 0.277393 | 3.09382 | 2(Loss) | true |
| Glaze | 850.849 | 0.158614 | 419.757ms | 3223 | 80 | 2626.58 | 3612.5 | 0 | 3.56096 | 3(Loss) | true |
| simdjson (ondemand) | 717.04 | 0.087262 | 484.263ms | 3223 | 2560 | 35819.9 | 4286.64 | 0.0855853 | 4.22143 | 4(Loss) | true |
