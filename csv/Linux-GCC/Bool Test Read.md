
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 398.877 | 0.192871 | 218.808ms | 905 | 4890 | 85165.1 | 2163.76 | 0.434351 | 6.12905 | 1(Win) | true |
| simdjson (ondemand) | 202.755 | 0.0546946 | 437.01ms | 905 | 30 | 162.616 | 4256.73 | 0.321306 | 12.1305 | 2(Loss) | true |
