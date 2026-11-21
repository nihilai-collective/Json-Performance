
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2221.69 | 0.122703 | 175.407ms | 3873 | 80 | 332.911 | 1662.51 | 0.625383 | 1(Win) | true |
| Jsonifier (two-stage) | 2177.98 | 0.147448 | 181.204ms | 3873 | 80 | 500.212 | 1695.88 | 0.0545144 | 2(Loss) | true |
| Glaze | 1253.29 | 0.173786 | 310.965ms | 3873 | 4890 | 128272 | 2947.12 | 0.361611 | 3(Loss) | true |
| simdjson (ondemand) | 612.841 | 0.0849336 | 619.144ms | 3873 | 4890 | 128135 | 6026.98 | 0.681567 | 4(Loss) | true |
