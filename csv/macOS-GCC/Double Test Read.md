
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 356.9 | 0.324737 | 501.794ms | 1811 | 4890 | 1.20758e+06 | 4839.19 | 7.80096 | -(Win) | false |
| simdjson (ondemand) | 180.372 | 0.324813 | 1028.11ms | 1811 | 4890 | 4.73016e+06 | 9575.24 | 1.52377 | 2(Loss) | true |
