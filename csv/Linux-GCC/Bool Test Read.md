
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 522.104 | 0.0499673 | 882.387ms | 905 | 4890 | 3336.28 | 1653.07 | 0.152981 | 10.0821 | 55.4608 | 5.50387 | 0.00111876 | 0.0001053 | 7.00494e-06 | 1(Win) | true |
| simdjson (ondemand) | 227.63 | 0.0366239 | 1093.27ms | 905 | 2560 | 4936.36 | 3791.57 | 0.0395977 | 22.8533 | 104.421 | 9.82431 | 0.0789814 | 0.000111792 | 7.33771e-06 | 2(Loss) | true |
