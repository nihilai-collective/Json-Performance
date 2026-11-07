
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 964.526 | 0.107798 | 183.769ms | 1811 | 640 | 2384.59 | 1790.62 | 0.0873362 | 2.52836 | 1(Win) | true |
| Jsonifier (two-stage) | 365.036 | 0.17201 | 481.406ms | 1811 | 4890 | 323878 | 4731.33 | 0.00740634 | 6.74627 | 2(Loss) | true |
| Glaze | 308.205 | 0.12873 | 399.414ms | 1811 | 80 | 4162.97 | 5603.75 | 0.0223115 | 7.99573 | 3(Loss) | true |
| simdjson (ondemand) | 140.301 | 0.0712885 | 1239.44ms | 1811 | 30 | 2310.34 | 12310 | 0.0270856 | 17.6109 | 4(Loss) | true |
