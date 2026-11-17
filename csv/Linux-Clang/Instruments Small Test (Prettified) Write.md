
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14030.9 | 0.195532 | 797.752ms | 9249 | 40 | 60.4385 | 628.65 | 0.00265125 | 0.383804 | 1.22889 | 0.293221 | 0.00021624 | 1.6218e-05 | 0 | 1(Win) | true |
| Glaze | 2817.69 | 0.171949 | 1052.28ms | 9249 | 2560 | 74172.6 | 3130.41 | 0.124081 | 1.82279 | 3.89242 | 0.651206 | 0.000482865 | 2.8846e-05 | 9.29155e-06 | 2(Loss) | true |
