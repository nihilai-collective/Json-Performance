
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1690.99 | 0.21386 | 180.035ms | 2632 | 4890 | 49278.4 | 1484.38 | 1.56789 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 1398.42 | 0.272693 | 221.501ms | 2632 | 4890 | 117153 | 1794.93 | 5.46287 | -(Loss) | false |
| Jsonifier (two-stage) | 1362.86 | 0.388569 | 227.093ms | 2632 | 1280 | 65556.2 | 1841.76 | 1.99078 | 3(Loss) | true |
| simdjson (ondemand) | 1175.52 | 0.0833648 | 240.326ms | 2632 | 640 | 2027.95 | 2135.29 | 0.066414 | 4(Loss) | true |
