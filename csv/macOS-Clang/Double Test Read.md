
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 855.821 | 0.235281 | 204.462ms | 1811 | 30 | 676.34 | 2018.07 | 0.00165172 | 1(Win) | true |
| Glaze | 767.589 | 0.118747 | 226.811ms | 1811 | 80 | 571.1 | 2250.04 | 0.0472437 | 2(Loss) | true |
| simdjson (ondemand) | 250.334 | 2.49403 | 630.644ms | 1811 | 320 | 9.47439e+06 | 6899.2 | 0.829197 | 3(Loss) | true |
