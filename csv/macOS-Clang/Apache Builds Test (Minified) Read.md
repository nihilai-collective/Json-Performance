
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1571.61 | 0.171894 | 5783.92ms | 94653 | 160 | 1.55962e+06 | 57436.7 | 0.0611699 | 1(Win) | true |
| Glaze | 1127.17 | 0.0709111 | 8143.47ms | 94653 | 4890 | 1.57698e+07 | 80083.8 | 0.154834 | 2(Loss) | true |
| Jsonifier (two-stage) | 1089.11 | 0.214395 | 8365.48ms | 94653 | 320 | 1.01041e+07 | 82882.2 | 0.0630395 | 3(Loss) | true |
| simdjson (ondemand) | 869.374 | 0.12164 | 5320.17ms | 94653 | 640 | 1.02091e+07 | 103831 | 0.0597299 | 4(Loss) | true |
