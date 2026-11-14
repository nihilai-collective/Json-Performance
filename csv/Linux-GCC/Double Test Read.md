
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 406.432 | 0.0639227 | 435.236ms | 1811 | 30 | 221.357 | 4249.43 | 0.05651 | 6.05229 | 1(Win) | true |
| simdjson (ondemand) | 252.639 | 0.0807163 | 703.245ms | 1811 | 30 | 913.444 | 6836.27 | 0.176332 | 9.76299 | 2(Loss) | true |
