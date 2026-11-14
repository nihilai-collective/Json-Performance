
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2184.17 | 0.148977 | 141.972ms | 2632 | 160 | 468.986 | 1149.21 | 0.0684783 | 1(Win) | true |
| Jsonifier (two-stage) | 1737.25 | 0.151979 | 176.184ms | 2632 | 80 | 385.749 | 1444.85 | 0.0761905 | 2(Loss) | true |
| Glaze | 1718.59 | 0.167535 | 170.247ms | 2632 | 640 | 3831.96 | 1460.54 | 0.222909 | 3(Loss) | true |
| simdjson (ondemand) | 1225.24 | 0.171429 | 231.039ms | 2632 | 640 | 7893.65 | 2048.63 | 0.118053 | 4(Loss) | true |
