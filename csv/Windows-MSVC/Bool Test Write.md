
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 948.434 | 0.527895 | 106.712ms | 905 | 40 | 923.077 | 910 | 0.364964 | 2.55887 | 1(Win) | true |
| Glaze | 87.7548 | 0.746724 | 1089.09ms | 905 | 1280 | 6.90376e+06 | 9835.08 | 0.0103276 | 28.1254 | 2(Loss) | true |
