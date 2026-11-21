
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 551.626 | 0.162734 | 370.007ms | 1997 | 80 | 2525.32 | 3452.5 | 0 | 4.45734 | 1(Win) | true |
| Glaze | 388.602 | 0.101792 | 482.521ms | 1798 | 80 | 1613.92 | 4412.5 | 0.0566893 | 6.33075 | 2(Loss) | true |
