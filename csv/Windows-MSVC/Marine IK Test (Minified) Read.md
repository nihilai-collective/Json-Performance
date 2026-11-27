
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 667.88 | 0.961334 | 8278.98ms | 1834197 | 80 | 5.07146e+10 | 2.61907e+06 | 1.17924 | 4.55031 | 1(Win) | true |
| Jsonifier (two-stage) | 522.747 | 1.48468 | 10067.3ms | 1834197 | 30 | 7.40452e+10 | 3.34622e+06 | 1.56382 | 5.81374 | 2(Loss) | true |
| simdjson (ondemand) | 356.83 | 0.87905 | 7285.06ms | 1834197 | 30 | 5.5708e+10 | 4.90213e+06 | 2.42089 | 8.51683 | 3(Loss) | true |
| Glaze | 304.668 | 0.637188 | 8694.36ms | 1834197 | 80 | 1.07069e+11 | 5.74143e+06 | 0.458622 | 9.97586 | 4(Loss) | true |
