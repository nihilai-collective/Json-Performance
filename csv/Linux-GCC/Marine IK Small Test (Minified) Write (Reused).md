
----
### Marine IK Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1524.38 | 0.295867 | 1028.45ms | 4918 | 40 | 3314.69 | 3076.78 | 0.0935294 | 3.42233 | 11.2717 | 1.32351 | 0.000523587 | 5.08337e-05 | 2.03335e-05 | 1(Win) | true |
| Jsonifier | 1445.78 | 0.135504 | 1023.64ms | 4604 | 2560 | 43351.6 | 3036.91 | 0.313411 | 3.60046 | 9.42832 | 0.5404 | 0.000319016 | 4.36102e-05 | 1.51872e-05 | 2(Loss) | true |
| Glaze | 1326.76 | 0.0540367 | 1050.12ms | 4604 | 4890 | 15637.6 | 3309.35 | 0.0137226 | 3.92119 | 12.2024 | 0.968289 | 0.000759409 | 3.29579e-05 | 1.08823e-05 | 3(Loss) | true |
