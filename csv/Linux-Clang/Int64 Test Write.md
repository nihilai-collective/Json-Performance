
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 338.329 | 0.0574712 | 375.895ms | 1313 | 40 | 180.972 | 3701.05 | 0.139344 | 7.26771 | 1(Win) | true |
| Glaze | 293.034 | 0.144799 | 432.837ms | 1313 | 30 | 1148.53 | 4273.13 | 0.170543 | 8.39855 | 2(Loss) | true |
