
----
### Marine IK Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7389.75 | 0.057431 | 320.357ms | 24893 | 30 | 102.12 | 3212.53 | 0.351545 | 0.332103 | 1(Win) | true |
| Glaze | 3644.36 | 0.109069 | 657.461ms | 24579 | 80 | 3937.15 | 6431.96 | 0.00408101 | 0.676466 | 2(Loss) | true |
| simdjson (reflection) | 555.005 | 0.0627164 | 4247.25ms | 24893 | 2560 | 1.84231e+06 | 42774 | 0.220962 | 4.45794 | 3(Loss) | true |
