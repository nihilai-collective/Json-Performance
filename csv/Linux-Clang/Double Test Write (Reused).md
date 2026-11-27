
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 946.191 | 0.0240476 | 212.886ms | 1997 | 160 | 37.4855 | 2012.79 | 0.0363433 | 2.58251 | 1(Win) | true |
| Glaze | 600.787 | 0.0563398 | 300.751ms | 1798 | 40 | 103.426 | 2854.1 | 0.109904 | 4.08323 | 2(Loss) | true |
