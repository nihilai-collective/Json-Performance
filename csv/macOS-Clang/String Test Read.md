
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1345.24 | 0.0528483 | 704.458ms | 9578 | 80 | 1030.16 | 6790.09 | 0.0402999 | 1(Win) | true |
| Jsonifier | 1331.11 | 0.0876542 | 701.165ms | 9578 | 4890 | 176919 | 6862.14 | 0.135688 | 2(Loss) | true |
| Glaze | 1117.37 | 0.0415545 | 815.917ms | 9578 | 160 | 1846.34 | 8174.8 | 0.323374 | 3(Loss) | true |
| simdjson (ondemand) | 812.172 | 0.0537262 | 1165.69ms | 9578 | 40 | 1460.45 | 11246.8 | 0.00815117 | 4(Loss) | true |
