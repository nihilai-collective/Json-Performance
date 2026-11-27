
----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22958.1 | 0.239136 | 40.6875ms | 9255 | 80 | 67.6177 | 384.45 | 0.0325034 | 0.100108 | 1(Win) | true |
| Glaze | 4312.14 | 0.0661496 | 216.406ms | 9255 | 160 | 293.319 | 2046.84 | 0.0721144 | 0.566783 | 2(Loss) | true |
| simdjson (reflection) | 586.751 | 0.422092 | 1552.53ms | 9255 | 80 | 322514 | 15042.6 | 0.347053 | 4.21209 | 3(Loss) | true |
