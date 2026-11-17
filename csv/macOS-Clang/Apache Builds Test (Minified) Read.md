
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1557.22 | 0.0804021 | 6244.62ms | 94653 | 1280 | 2.78044e+06 | 57967.5 | 0.0456418 | 1(Win) | true |
| Glaze | 1131.16 | 0.0914735 | 8235.87ms | 94653 | 4890 | 2.60568e+07 | 79801.5 | 0.165361 | 2(Loss) | true |
| Jsonifier (two-stage) | 1099.23 | 0.492304 | 8416.27ms | 94653 | 30 | 4.9032e+06 | 82119.5 | 0.223833 | 3(Loss) | true |
| simdjson (ondemand) | 788.784 | 0.308542 | 5479ms | 94653 | 160 | 1.99481e+07 | 114440 | 0.0040795 | 4(Loss) | true |
