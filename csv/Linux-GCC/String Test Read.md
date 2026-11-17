
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1118.65 | 0.117397 | 825.624ms | 9578 | 4890 | 449351 | 8165.46 | 0.550211 | 2.20633 | 1(Win) | true |
| Jsonifier (generic) | 766.388 | 0.0284583 | 1193.51ms | 9578 | 30 | 345.137 | 11918.6 | 0.326604 | 3.22326 | 2(Loss) | true |
