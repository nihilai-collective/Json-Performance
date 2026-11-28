
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5910.67 | 0.096548 | 76.48ms | 4215 | 160 | 68.9808 | 680.081 | 0.0266583 | 0.403302 | 1(Win) | true |
| Glaze | 2288.14 | 0.0646191 | 184.631ms | 4215 | 160 | 206.191 | 1756.77 | 0.0359454 | 1.0663 | 2(Loss) | true |
