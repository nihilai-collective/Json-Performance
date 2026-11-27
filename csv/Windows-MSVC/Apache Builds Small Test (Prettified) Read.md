
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1317.04 | 0.314235 | 248.576ms | 3370 | 2560 | 150526 | 2440.23 | 0.188535 | 1.85722 | 1(Win) | true |
| Jsonifier (two-stage) | 1257.66 | 0.245687 | 259.283ms | 3370 | 4890 | 192755 | 2555.44 | 0.141221 | 1.94532 | 2(Loss) | true |
| Glaze | 1076.68 | 0.14719 | 309.307ms | 3370 | 80 | 1544.3 | 2985 | 0.251889 | 2.28281 | 3(Loss) | true |
| simdjson (ondemand) | 828.187 | 0.265962 | 402.921ms | 3370 | 160 | 17043.6 | 3880.62 | 0.436752 | 2.96787 | 4(Loss) | true |
