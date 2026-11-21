
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 766.136 | 0.22494 | 730.395ms | 4630 | 2560 | 430252 | 5763.35 | 1.56219 | 1(Win) | true |
| Jsonifier (two-stage) | 738.101 | 0.0629368 | 800.395ms | 4630 | 80 | 1134.04 | 5982.26 | 0.468561 | 2(Loss) | true |
| simdjson (ondemand) | 512.839 | 0.0610274 | 1172.96ms | 4630 | 80 | 2208.72 | 8609.94 | 0.126872 | 3(Loss) | true |
| Glaze | 502.918 | 0.175254 | 1002.67ms | 4630 | 4890 | 1.15775e+06 | 8779.78 | 1.87986 | 4(Loss) | true |
