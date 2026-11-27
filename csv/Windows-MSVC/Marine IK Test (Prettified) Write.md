
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2972.74 | 0.951159 | 5039.21ms | 10018896 | 30 | 2.80384e+10 | 3.21413e+06 | 3.12807 | 1.02235 | -(Win) | false |
| Glaze | 1204.76 | 0.971549 | 5522.56ms | 9930228 | 40 | 2.33295e+11 | 7.86064e+06 | 0.143019 | 2.52276 | 2(Loss) | true |
