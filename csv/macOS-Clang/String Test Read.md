
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1398.09 | 0.1263 | 663.278ms | 9578 | 1280 | 87157 | 6533.43 | 0.0382914 | 1(Win) | true |
| Glaze | 1199.64 | 0.0535545 | 774.151ms | 9578 | 320 | 5320.95 | 7614.18 | 0.320824 | 2(Loss) | true |
| simdjson (ondemand) | 877.151 | 0.203626 | 1038.06ms | 9578 | 1280 | 575542 | 10413.6 | 0.157516 | 3(Loss) | true |
| Jsonifier (two-stage) | 748.71 | 0.0959612 | 1229.57ms | 9578 | 30 | 4111.83 | 12200 | 0.181908 | 4(Loss) | true |
