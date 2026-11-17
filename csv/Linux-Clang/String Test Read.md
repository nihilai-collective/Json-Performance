
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1221.65 | 0.0385941 | 758.941ms | 9578 | 80 | 666.177 | 7477.02 | 0.160414 | 2.01959 | 1(Win) | true |
| Jsonifier (generic) | 760.959 | 0.30294 | 1224.18ms | 9578 | 640 | 846291 | 12003.7 | 0.309711 | 3.24643 | 2(Loss) | true |
