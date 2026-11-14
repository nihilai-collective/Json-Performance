
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1135.05 | 0.104651 | 797.794ms | 9578 | 4890 | 346832 | 8047.49 | 0.00303553 | 2.17348 | 1(Win) | true |
| Jsonifier (generic) | 683.808 | 0.0779467 | 1345.46ms | 9578 | 4890 | 530135 | 13358 | 0.230235 | 3.61314 | 2(Loss) | true |
