
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1356.22 | 0.0275276 | 1404.14ms | 9578 | 4890 | 16808.6 | 6735.09 | 0.136123 | 3.7955 | 19.2036 | 3.36281 | 0.00137799 | 2.513e-05 | 7.1739e-06 | 1(Win) | true |
| simdjson (ondemand) | 1299.88 | 0.0392288 | 1432.03ms | 9578 | 1280 | 9726.65 | 7027.02 | 0.00522509 | 3.9293 | 17.5663 | 2.97212 | 0.00271374 | 1.6395e-05 | 1.06037e-06 | 2(Loss) | true |
