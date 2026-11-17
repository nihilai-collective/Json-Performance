
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1300.55 | 0.26714 | 235.611ms | 2632 | 80 | 2126.58 | 1930 | 0.129702 | 1.87405 | 1(Win) | true |
| Glaze | 1278.81 | 0.272128 | 234.923ms | 2632 | 4890 | 139513 | 1962.82 | 0.0701918 | 1.90636 | 2(Loss) | true |
| Jsonifier (two-stage) | 1218.11 | 0.132752 | 252.096ms | 2632 | 320 | 2394.59 | 2060.62 | 0.181653 | 2.00469 | 3(Loss) | true |
| simdjson (ondemand) | 1088.18 | 0.200812 | 270.63ms | 2632 | 30 | 643.678 | 2306.67 | 0.144718 | 2.25227 | 4(Loss) | true |
