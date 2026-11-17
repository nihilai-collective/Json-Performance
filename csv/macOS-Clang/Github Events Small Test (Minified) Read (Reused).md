
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2206.88 | 0.24161 | 90.605ms | 1691 | 160 | 498.745 | 730.744 | 0.209109 | 1(Win) | true |
| Jsonifier (two-stage) | 1781.38 | 0.173367 | 122.925ms | 1691 | 160 | 394.118 | 905.288 | 0.258874 | 2(Loss) | true |
| Glaze | 1744.69 | 0.224546 | 107.062ms | 1691 | 1280 | 5514.04 | 924.327 | 0.0321283 | 3(Loss) | true |
| simdjson (ondemand) | 1306.66 | 0.0932818 | 141.205ms | 1691 | 640 | 848.276 | 1234.19 | 0.0881633 | 4(Loss) | true |
