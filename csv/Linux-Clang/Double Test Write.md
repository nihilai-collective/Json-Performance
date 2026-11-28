
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 363.335 | 0.251719 | 532.513ms | 1997 | 1280 | 222835 | 5241.68 | 0.347525 | 6.78021 | 1(Win) | true |
| Glaze | 286.852 | 0.088497 | 609.188ms | 1798 | 30 | 839.54 | 5977.67 | 0.172605 | 8.59192 | 2(Loss) | true |
