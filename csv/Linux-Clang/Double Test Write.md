
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 367.733 | 0.0166208 | 523.324ms | 1997 | 160 | 118.553 | 5179 | 0.314225 | 6.69881 | 1(Win) | true |
| Glaze | 287.846 | 0.0615691 | 618.887ms | 1798 | 40 | 538.076 | 5957.02 | 0.00153882 | 8.56449 | 2(Loss) | true |
