
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15158.3 | 0.0809382 | 769.466ms | 7376 | 1280 | 180.575 | 464.056 | 0.150059 | 0.367964 | 1.1833 | 0.169469 | 0.000135787 | 1.85356e-05 | 2.9657e-06 | 1(Win) | true |
| Glaze | 3118.15 | 0.12475 | 954.294ms | 7376 | 4890 | 38729.1 | 2255.92 | 0.237924 | 1.67227 | 4.11781 | 0.685738 | 0.000138098 | 5.75015e-05 | 1.83262e-05 | 2(Loss) | true |
| simdjson (reflection) | 536.984 | 0.164989 | 2064.6ms | 7376 | 640 | 298957 | 13099.7 | 0.0540514 | 9.54069 | 39.4162 | 8.02888 | 0.0127362 | 7.90147e-05 | 2.47848e-05 | 3(Loss) | true |
