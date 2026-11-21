
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1853.21 | 0.932813 | 154.525ms | 2632 | 160 | 25540.6 | 1354.44 | 2.17179 | 1(Win) | true |
| Jsonifier (two-stage) | 1549.32 | 0.405694 | 189.634ms | 2632 | 160 | 6912.08 | 1620.11 | 0.878723 | 2(Loss) | true |
| Glaze | 1496.36 | 0.207082 | 206.488ms | 2632 | 4890 | 59005.2 | 1677.45 | 0.0291937 | 3(Loss) | true |
| simdjson (ondemand) | 1122.28 | 0.285448 | 257.05ms | 2632 | 640 | 26085.6 | 2236.57 | 0.485957 | 4(Loss) | true |
