
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4629.65 | 0.0811469 | 199.469ms | 9578 | 80 | 205.063 | 1973 | 0.0126695 | 0.527964 | 1(Win) | true |
| Glaze | 1863.05 | 0.23862 | 467.829ms | 9578 | 1280 | 175196 | 4902.86 | 0.151112 | 1.32147 | 2(Loss) | true |
