
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1885.92 | 0.452983 | 219.571ms | 3223 | 4890 | 266531 | 1629.81 | 0.786242 | 1(Win) | true |
| Jsonifier (two-stage) | 1301.42 | 0.694644 | 289.9ms | 3223 | 1280 | 344525 | 2361.8 | 0.24618 | 2(Loss) | true |
| Glaze | 1241.9 | 0.440096 | 306.229ms | 3223 | 2560 | 303729 | 2475 | 0.373104 | 3(Loss) | true |
| simdjson (reflection) | 1103.41 | 0.240311 | 333.814ms | 3223 | 4890 | 219131 | 2785.64 | 0.238791 | 4(Loss) | true |
| simdjson (ondemand) | 1031.11 | 0.219938 | 367.608ms | 3223 | 4890 | 210195 | 2980.96 | 1.11806 | 5(Loss) | true |
