
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1060.85 | 0.0448136 | 491.7ms | 4630 | 40 | 139.167 | 4162.25 | 0.0188164 | 2.31908 | 1(Win) | true |
| Jsonifier (two-stage) | 967.264 | 0.0344142 | 549.212ms | 4630 | 80 | 197.441 | 4564.95 | 0.162368 | 2.54342 | 2(Loss) | true |
| Glaze | 825.901 | 0.105667 | 636.496ms | 4630 | 40 | 1276.57 | 5346.3 | 0.144233 | 2.98322 | 3(Loss) | true |
| simdjson (ondemand) | 782.619 | 0.358998 | 645.188ms | 4630 | 1280 | 525114 | 5641.97 | 0.300009 | 3.14749 | 4(Loss) | true |
