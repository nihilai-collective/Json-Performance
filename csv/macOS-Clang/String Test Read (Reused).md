
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1528.92 | 0.116353 | 342.952ms | 4215 | 30 | 280.74 | 2629.13 | 0.106386 | 1(Win) | true |
| Glaze | 1042.25 | 0.101445 | 477.3ms | 4215 | 80 | 1224.64 | 3856.8 | 0.0110183 | 2(Loss) | true |
| simdjson (ondemand) | 818.684 | 0.100498 | 552.291ms | 4215 | 4890 | 119066 | 4910 | 0.135294 | 3(Loss) | true |
