
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 691.966 | 0.321045 | 302.413ms | 1811 | 2560 | 164376 | 2495.94 | 0.246667 | 3.53836 | 1(Win) | true |
| Glaze | 354.736 | 0.0775795 | 500.168ms | 1798 | 160 | 2250 | 4833.75 | 0.257931 | 6.94312 | 2(Loss) | true |
