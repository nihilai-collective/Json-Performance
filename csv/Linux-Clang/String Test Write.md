
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1829.19 | 0.0376506 | 224.816ms | 4215 | 160 | 109.532 | 2197.55 | 0.188062 | 1.33722 | 1(Win) | true |
| Glaze | 931.169 | 0.283951 | 435.224ms | 4215 | 1280 | 192325 | 4316.87 | 0.361626 | 2.64302 | 2(Loss) | true |
