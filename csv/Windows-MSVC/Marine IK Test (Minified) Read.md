
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 675.188 | 0.109541 | 8284.29ms | 1834197 | 30 | 2.4161e+08 | 2.59073e+06 | 0.022897 | 3.66685 | 1(Win) | true |
| Jsonifier (two-stage) | 580.558 | 0.34103 | 9453.22ms | 1834197 | 80 | 8.44648e+09 | 3.01301e+06 | 1.32299 | 4.26439 | 2(Loss) | true |
| simdjson (ondemand) | 202.529 | 1.94414 | 5951.25ms | 1834197 | 40 | 1.12781e+12 | 8.63693e+06 | 0.698015 | 12.2241 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 192.69 | 1.39848 | 6123.42ms | 1834197 | 40 | 6.44682e+11 | 9.07794e+06 | 5.02767 | 12.8485 | -(Loss) | false |
