
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1636.18 | 0.0702177 | 304.104ms | 4215 | 80 | 238.075 | 2456.78 | 0.0610184 | 1(Win) | true |
| Glaze | 1079.08 | 0.230129 | 453.871ms | 4215 | 640 | 47033.5 | 3725.14 | 0.0165235 | 2(Loss) | true |
| simdjson (ondemand) | 854.229 | 0.144061 | 534.922ms | 4215 | 2560 | 117647 | 4705.69 | 0.22353 | 3(Loss) | true |
