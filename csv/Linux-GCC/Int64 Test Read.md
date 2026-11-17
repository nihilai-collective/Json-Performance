
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 851.936 | 0.03401 | 451.118ms | 3862 | 30 | 64.8552 | 4323.2 | 0.0454703 | 2.88744 | 1(Win) | true |
| simdjson (ondemand) | 588.465 | 0.0514882 | 638.165ms | 3862 | 80 | 830.787 | 6258.81 | 0.271754 | 4.19029 | 2(Loss) | true |
