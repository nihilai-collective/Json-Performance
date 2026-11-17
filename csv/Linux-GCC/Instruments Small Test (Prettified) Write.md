
----
### Instruments Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22463.7 | 0.0614763 | 41.7436ms | 9249 | 640 | 37.2927 | 392.658 | 0.0394105 | 0.102624 | 1(Win) | true |
| Glaze | 3345.7 | 0.266841 | 267.229ms | 9249 | 2560 | 126695 | 2636.38 | 0.0857893 | 0.732497 | 2(Loss) | true |
| simdjson (reflection) | 516.925 | 0.0858658 | 1741.87ms | 9249 | 4890 | 1.04974e+06 | 17063.5 | 0.211298 | 4.78179 | 3(Loss) | true |
