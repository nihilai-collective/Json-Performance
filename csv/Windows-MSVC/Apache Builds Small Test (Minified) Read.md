
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1036.68 | 0.281633 | 258.136ms | 2632 | 80 | 3719.94 | 2421.25 | 0.155119 | 2.3529 | 1(Win) | true |
| Jsonifier (two-stage) | 957.129 | 0.234735 | 277.206ms | 2632 | 80 | 3031.65 | 2622.5 | 0.0952381 | 2.55958 | 2(Loss) | true |
| Glaze | 860.534 | 0.202142 | 317.009ms | 2632 | 160 | 5562.5 | 2916.88 | 0.10725 | 2.84528 | 3(Loss) | true |
| simdjson (ondemand) | 685.467 | 0.210137 | 379.694ms | 2632 | 4890 | 289544 | 3661.84 | 0.204289 | 3.58281 | 4(Loss) | true |
