
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1731.48 | 0.0674263 | 538.046ms | 9578 | 40 | 506.097 | 5275.43 | 0.129521 | 1.42235 | 1(Win) | true |
| Glaze | 1350.68 | 0.102763 | 686.042ms | 9578 | 4890 | 236175 | 6762.76 | 0.152992 | 1.82564 | 2(Loss) | true |
| simdjson (ondemand) | 1201.2 | 0.0594594 | 769.49ms | 9578 | 40 | 817.743 | 7604.27 | 0.0803922 | 2.05335 | 3(Loss) | true |
| Jsonifier (two-stage) | 1018.88 | 0.33292 | 919.859ms | 9578 | 320 | 285057 | 8965.02 | 0.112777 | 2.42253 | 4(Loss) | true |
