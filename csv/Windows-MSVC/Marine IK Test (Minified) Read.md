
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 669.037 | 0.217812 | 8145.18ms | 1834197 | 160 | 5.18889e+09 | 2.61454e+06 | 0.28057 | 4.54256 | 1(Win) | true |
| Jsonifier (two-stage) | 581.156 | 0.434718 | 9329.74ms | 1834197 | 160 | 2.73931e+10 | 3.00991e+06 | 0.168249 | 5.22942 | 2(Loss) | true |
| simdjson (ondemand) | 352.465 | 0.493074 | 7453.75ms | 1834197 | 80 | 4.79044e+10 | 4.96284e+06 | 0.717808 | 8.62294 | 3(Loss) | true |
| Glaze | 320.616 | 0.261866 | 8237.25ms | 1834197 | 30 | 6.12351e+09 | 5.45583e+06 | 0.633505 | 9.47961 | 4(Loss) | true |
