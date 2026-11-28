
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 954.302 | 0.0519497 | 212.551ms | 1997 | 160 | 171.977 | 1995.69 | 0.0909034 | 2.56093 | 1(Win) | true |
| Glaze | 593.306 | 0.0470431 | 302.94ms | 1798 | 80 | 147.878 | 2890.09 | 0.233669 | 4.13563 | 2(Loss) | true |
