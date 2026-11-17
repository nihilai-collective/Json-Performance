
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2207.77 | 0.129483 | 207.206ms | 4390 | 80 | 482.319 | 1896.31 | 0.0257144 | 1(Win) | true |
| Jsonifier (two-stage) | 1390.98 | 0.234922 | 375.402ms | 4390 | 1280 | 63995.2 | 3009.85 | 4.35843 | 2(Loss) | true |
| Glaze | 1095.73 | 0.217956 | 409.541ms | 4390 | 40 | 2774.08 | 3820.85 | 0.107626 | 3(Loss) | true |
| simdjson (ondemand) | 732.972 | 0.290368 | 581.459ms | 4390 | 2560 | 704193 | 5711.85 | 0.55549 | 4(Loss) | true |
