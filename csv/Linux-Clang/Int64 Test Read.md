
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 904.979 | 0.261039 | 411.556ms | 3862 | 4890 | 551907 | 4069.81 | 0.0380865 | 2.71787 | 1(Win) | true |
| simdjson (ondemand) | 658.633 | 0.189172 | 558.534ms | 3862 | 2560 | 286477 | 5592.02 | 0.0683639 | 3.74099 | 2(Loss) | true |
