
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1416.18 | 0.379846 | 213.335ms | 2632 | 2560 | 116035 | 1772.42 | 0.0792777 | 1.72033 | 1(Win) | true |
| Glaze | 1382.96 | 0.242072 | 219.725ms | 2632 | 80 | 1544.3 | 1815 | 0.137552 | 1.76226 | 2(Loss) | true |
| Jsonifier (two-stage) | 1331.6 | 0.183386 | 226.095ms | 2632 | 160 | 1911.95 | 1885 | 0.0662691 | 1.83344 | 3(Loss) | true |
| simdjson (ondemand) | 1316.97 | 0.115971 | 222.053ms | 2632 | 320 | 1563.38 | 1905.94 | 0.0163934 | 1.85217 | 4(Loss) | true |
