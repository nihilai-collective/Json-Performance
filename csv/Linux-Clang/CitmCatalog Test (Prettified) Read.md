
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3449.43 | 0.221958 | 8393.95ms | 1151920 | 80 | 3.99743e+07 | 318475 | 0.00255521 | 1.45818 | 6.59617 | 1.04633 | 0.00625789 | 0.0549414 | 0.000159234 | 1(Win) | true |
| Jsonifier | 2900.18 | 0.157957 | 9945.56ms | 1151920 | 160 | 5.72787e+07 | 378790 | 0.118973 | 1.74305 | 7.48619 | 1.65172 | 0.00477962 | 0.0192471 | 7.84071e-05 | 2(Loss) | true |
| Glaze | 2564.34 | 0.0951333 | 5553.37ms | 1151920 | 160 | 2.65754e+07 | 428398 | 0.0608697 | 1.96429 | 8.62597 | 1.67904 | 0.00759814 | 0.0137861 | 0.000185896 | 3(Loss) | true |
| simdjson (ondemand) | 2386.86 | 0.063156 | 5960.24ms | 1151920 | 640 | 5.40755e+07 | 460252 | 0.194508 | 2.10247 | 8.90783 | 1.27864 | 0.00720599 | 0.051008 | 0.00012099 | 4(Loss) | true |
