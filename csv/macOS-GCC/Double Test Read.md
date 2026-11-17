
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 400.31 | 0.18586 | 439.252ms | 1811 | 4890 | 314430 | 4314.41 | 0.0483852 | 1(Win) | true |
| simdjson (ondemand) | 202.303 | 0.288645 | 861.731ms | 1811 | 640 | 388631 | 8537.2 | 0.396677 | 2(Loss) | true |
