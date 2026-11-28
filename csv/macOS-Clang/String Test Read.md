
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.88 | 0.141362 | 358.536ms | 4215 | 4890 | 115962 | 3444.85 | 0.69572 | 1(Win) | true |
| Glaze | 759.424 | 0.252586 | 533.044ms | 4215 | 2560 | 457600 | 5293.14 | 0.294174 | 2(Loss) | true |
| simdjson (ondemand) | 654.801 | 0.224117 | 667.951ms | 4215 | 30 | 5678.67 | 6138.87 | 2.05421 | 3(Loss) | true |
