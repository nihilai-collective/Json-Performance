
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 881.911 | 0.0567143 | 225.478ms | 1997 | 40 | 60 | 2159.5 | 0.05869 | 2.77181 | 1(Win) | true |
| simdjson (reflection) | 715.801 | 0.0283527 | 277.379ms | 1997 | 80 | 45.5252 | 2660.64 | 0.00422813 | 3.4242 | 2(Loss) | true |
| Glaze | 543.657 | 0.0495916 | 321.99ms | 1798 | 80 | 195.721 | 3154.03 | 0.0801206 | 4.51557 | 3(Loss) | true |
