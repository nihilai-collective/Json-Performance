
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 773.215 | 0.396234 | 1245.2ms | 9578 | 1280 | 2.80456e+06 | 11813.4 | 3.19107 | 1(Win) | true |
| simdjson (ondemand) | 657.417 | 0.239068 | 1401.7ms | 9578 | 4890 | 5.39536e+06 | 13894.2 | 0.098005 | 2(Loss) | true |
