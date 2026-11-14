
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1011.87 | 0.0705891 | 913.204ms | 9578 | 2560 | 103948 | 9027.15 | 0.206845 | 2.99578 | 1(Win) | true |
| Glaze | 824.104 | 0.0930682 | 1127.87ms | 9578 | 1280 | 136207 | 11083.9 | 0.740212 | 3.68058 | 2(Loss) | true |
| Jsonifier (two-stage) | 790.26 | 0.0811079 | 1163.93ms | 9578 | 1280 | 112498 | 11558.6 | 0.0811743 | 3.83801 | 3(Loss) | true |
| simdjson (ondemand) | 752.413 | 0.212275 | 1241.12ms | 9578 | 40 | 26564.1 | 12140 | 0.027465 | 4.03355 | 4(Loss) | true |
