
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2641.62 | 0.066313 | 98.1343ms | 2632 | 320 | 127.051 | 950.2 | 0.0315623 | 0.911408 | 1(Win) | true |
| Jsonifier (two-stage) | 2582.82 | 0.134849 | 101.527ms | 2632 | 30 | 51.523 | 971.833 | 0 | 0.93384 | 2(Loss) | true |
| Glaze | 2115.19 | 0.0277465 | 123.01ms | 2632 | 640 | 69.3858 | 1186.69 | 0.0131652 | 1.14455 | 3(Loss) | true |
| simdjson (ondemand) | 1549.33 | 0.131433 | 165.775ms | 2632 | 30 | 136.024 | 1620.1 | 0.283129 | 1.57196 | 4(Loss) | true |
