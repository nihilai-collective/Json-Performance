
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1495.8 | 0.32784 | 377.598ms | 4857 | 30 | 3091.95 | 3096.67 | 0 | 1.63569 | 1(Win) | true |
| Glaze | 1358.82 | 0.361141 | 389.555ms | 4857 | 1280 | 193988 | 3408.83 | 0.125893 | 1.80743 | 2(Loss) | true |
| Jsonifier (two-stage) | 1124.27 | 0.263602 | 477.686ms | 4857 | 40 | 4717.95 | 4120 | 0 | 2.18375 | 3(Loss) | true |
| simdjson (ondemand) | 1026.98 | 0.727137 | 503.483ms | 4857 | 320 | 344188 | 4510.31 | 0.0485235 | 2.39617 | 4(Loss) | true |
