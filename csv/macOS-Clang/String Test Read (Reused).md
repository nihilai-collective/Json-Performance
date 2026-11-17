
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2144.86 | 0.16097 | 690.925ms | 9578 | 4890 | 229800 | 4258.69 | 1.23626 | 1(Win) | true |
| Glaze | 1609.57 | 1.03906 | 799.978ms | 9578 | 160 | 556325 | 5674.98 | 0.15597 | 2(Loss) | true |
| simdjson (ondemand) | 1064.2 | 0.20639 | 1115.14ms | 9578 | 4890 | 1.53458e+06 | 8583.23 | 0.95652 | 3(Loss) | true |
| Jsonifier (two-stage) | 889.881 | 0.58144 | 1399.99ms | 9578 | 160 | 569922 | 10264.6 | 0.163021 | 4(Loss) | true |
