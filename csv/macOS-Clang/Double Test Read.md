
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 352.695 | 0.13613 | 540.078ms | 1811 | 40 | 1777.5 | 4896.88 | 0.0651352 | 1(Win) | true |
| simdjson (ondemand) | 182.315 | 1.05147 | 954.408ms | 1811 | 160 | 1.58745e+06 | 9473.17 | 0.823372 | 2(Loss) | true |
