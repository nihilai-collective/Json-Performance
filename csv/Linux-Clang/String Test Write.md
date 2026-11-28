
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1795.41 | 0.0730105 | 234.215ms | 4215 | 80 | 213.762 | 2238.9 | 0.101509 | 1.36281 | 1(Win) | true |
| Glaze | 891.597 | 0.0755795 | 453.5ms | 4215 | 30 | 348.326 | 4508.47 | 0.0295652 | 2.75954 | 2(Loss) | true |
