
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1857.69 | 0.1177 | 858.132ms | 2632 | 1280 | 3237.36 | 1351.18 | 0.551091 | 2.86655 | 11.1736 | 2.10828 | 0.00111043 | 6.11465e-05 | 1.45445e-05 | 1(Win) | true |
| simdjson (ondemand) | 1585.41 | 0.0611947 | 878.72ms | 2632 | 4890 | 4590.14 | 1583.23 | 0.00997348 | 3.33826 | 12.3047 | 2.15464 | 0.00178742 | 9.23042e-05 | 4.12572e-05 | 2(Loss) | true |
