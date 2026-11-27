
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1167.24 | 0.121547 | 219.536ms | 2632 | 80 | 546.553 | 2150.44 | 0.225607 | 1(Win) | true |
| simdjson (ondemand) | 946.273 | 0.210668 | 289.415ms | 2632 | 80 | 2498.19 | 2652.59 | 0.373236 | 2(Loss) | true |
