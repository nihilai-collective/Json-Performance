
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.06 | 0.0964151 | 5136.06ms | 10018896 | 80 | 8.51885e+08 | 3.38455e+06 | 0.0483681 | 0.876967 | 1(Win) | true |
| Glaze | 1019.7 | 1.31486 | 6359.47ms | 9930228 | 30 | 4.47353e+11 | 9.28723e+06 | 0.890396 | 2.42775 | 2(Loss) | true |
