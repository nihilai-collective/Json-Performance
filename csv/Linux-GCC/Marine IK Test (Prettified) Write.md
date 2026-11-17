
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5926.68 | 0.0661127 | 5033.45ms | 9930848 | 80 | 8.92912e+07 | 1.59799e+06 | 0.150878 | 0.417733 | 1(Win) | true |
| Glaze | 3159.42 | 0.310914 | 9221.39ms | 9930228 | 30 | 2.60559e+09 | 2.99745e+06 | 0.270497 | 0.783565 | 2(Loss) | true |
| simdjson (reflection) | 370.511 | 1.0179 | 7771.01ms | 10018896 | 30 | 2.06712e+12 | 2.57881e+07 | 0.647536 | 6.68212 | 3(Loss) | true |
