
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1954.36 | 0.228059 | 202.55ms | 3370 | 2560 | 36006.7 | 1644.47 | 0.0461514 | 1(Win) | true |
| Jsonifier | 1924.68 | 0.22142 | 203.723ms | 3370 | 2560 | 34996 | 1669.83 | 0.711 | 2(Loss) | true |
| Glaze | 1751.26 | 0.291128 | 213.831ms | 3370 | 160 | 4567.17 | 1835.19 | 0.0742983 | 3(Loss) | true |
| simdjson (ondemand) | 1321.91 | 0.435844 | 277.365ms | 3370 | 4890 | 549068 | 2431.24 | 1.95219 | 4(Loss) | true |
