
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1317.83 | 0.128641 | 829.787ms | 9578 | 2560 | 203530 | 6931.32 | 0.438808 | 1.87123 | 1(Win) | true |
| Jsonifier (generic) | 856.35 | 0.531552 | 1196.24ms | 9578 | 160 | 514350 | 10666.5 | 0.188377 | 2.88388 | 2(Loss) | true |
