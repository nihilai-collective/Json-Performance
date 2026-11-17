
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3958.58 | 0.621864 | 221.195ms | 9578 | 30 | 6177.09 | 2307.47 | 0.289754 | 0.61738 | 1(Win) | true |
| Glaze | 1846.6 | 0.19788 | 492.9ms | 9578 | 4890 | 468511 | 4946.55 | 0.101492 | 1.33322 | 2(Loss) | true |
