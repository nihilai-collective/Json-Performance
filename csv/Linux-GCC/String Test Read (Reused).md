
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.77 | 0.0649657 | 551.54ms | 9578 | 30 | 224.189 | 4207.87 | 0.333968 | 1.13385 | 1(Win) | true |
| Glaze | 1933.29 | 0.148326 | 614.029ms | 9578 | 30 | 1473.37 | 4724.73 | 0.331894 | 1.27285 | 2(Loss) | true |
| simdjson (ondemand) | 1366.39 | 0.0675675 | 795.829ms | 9578 | 30 | 612.069 | 6685 | 0.0299267 | 1.80472 | 3(Loss) | true |
| Jsonifier (two-stage) | 1086.64 | 0.0452524 | 1065.79ms | 9578 | 40 | 578.794 | 8406.02 | 0.152802 | 2.27179 | 4(Loss) | true |
