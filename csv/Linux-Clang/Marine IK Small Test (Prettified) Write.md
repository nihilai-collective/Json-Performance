
----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4651.77 | 0.115914 | 1250.44ms | 24893 | 1280 | 44792.2 | 5103.39 | 0.163854 | 1.10764 | 2.94738 | 0.378661 | 0.000150237 | 8.85038e-06 | 2.1969e-06 | 1(Win) | true |
| Glaze | 3313.52 | 0.076811 | 1451.84ms | 24579 | 4890 | 144380 | 7074.16 | 0.26284 | 1.5557 | 3.7399 | 0.481021 | 0.000378854 | 9.75112e-06 | 2.77058e-06 | 2(Loss) | true |
