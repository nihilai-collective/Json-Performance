
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1410.22 | 0.307447 | 183.989ms | 2632 | 2560 | 76661.2 | 1779.91 | 2.25514 | 1(Win) | true |
| Jsonifier (two-stage) | 1295.54 | 0.157574 | 202.079ms | 2632 | 80 | 745.645 | 1937.47 | 0.106984 | 2(Loss) | true |
| Glaze | 1160.87 | 0.460447 | 235.051ms | 2632 | 640 | 63437 | 2162.23 | 1.00241 | 3(Loss) | true |
| simdjson (ondemand) | 846.091 | 0.459345 | 299.863ms | 2632 | 30 | 5571.06 | 2966.67 | 0.706074 | 4(Loss) | true |
