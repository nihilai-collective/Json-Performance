
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6538.05 | 0.128087 | 1084.29ms | 24893 | 2560 | 55374.3 | 3631.02 | 0.270614 | 0.801925 | 1.8592 | 0.0919136 | 6.07757e-05 | 1.18319e-05 | 3.57781e-06 | 1(Win) | true |
| Glaze | 3904.29 | 0.0676596 | 1324.03ms | 24579 | 4890 | 80688.6 | 6003.74 | 0.138403 | 1.3362 | 3.76179 | 0.442166 | 0.000353012 | 1.30375e-05 | 4.25988e-06 | 2(Loss) | true |
| simdjson (reflection) | 558.5 | 0.324788 | 4969.96ms | 24893 | 640 | 1.2198e+07 | 42506.4 | 0.298272 | 9.20721 | 35.6502 | 5.72995 | 0.00903385 | 8.45494e-05 | 4.86457e-05 | 3(Loss) | true |
