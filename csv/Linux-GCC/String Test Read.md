
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1048.94 | 0.0971527 | 872.752ms | 9578 | 4890 | 350000 | 8708.13 | 0.00341659 | 2.35253 | 1(Win) | true |
| Jsonifier (generic) | 728.988 | 0.0854091 | 1266.41ms | 9578 | 4890 | 560050 | 12530.1 | 0.267538 | 3.38892 | 2(Loss) | true |
