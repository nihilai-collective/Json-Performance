
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1880.61 | 0.672706 | 106.356ms | 1691 | 1280 | 42594.1 | 857.52 | 0.0316237 | 1(Win) | true |
| Glaze | 1374.63 | 0.172956 | 134.723ms | 1691 | 4890 | 20132.4 | 1173.16 | 1.75363 | 2(Loss) | true |
| Jsonifier (two-stage) | 1327.8 | 0.460384 | 158.637ms | 1691 | 320 | 10004.9 | 1214.53 | 3.11343 | 3(Loss) | true |
| simdjson (ondemand) | 981.853 | 0.321584 | 173.511ms | 1691 | 2560 | 71420.6 | 1642.47 | 1.55953 | 4(Loss) | true |
