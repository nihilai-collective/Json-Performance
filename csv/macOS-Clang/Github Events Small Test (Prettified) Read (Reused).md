
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2112.62 | 0.258298 | 123.197ms | 2158 | 640 | 4052.1 | 974.159 | 1.22154 | 1(Win) | true |
| Glaze | 2005.09 | 0.454286 | 125.347ms | 2158 | 30 | 652.248 | 1026.4 | 0.40753 | 2(Loss) | true |
| Jsonifier | 1789.87 | 0.333536 | 135.114ms | 2158 | 2560 | 37651.8 | 1149.82 | 0.702633 | 3(Loss) | true |
| simdjson (ondemand) | 1316.67 | 0.425252 | 167.483ms | 2158 | 1280 | 56552.7 | 1563.06 | 4.80341 | 4(Loss) | true |
