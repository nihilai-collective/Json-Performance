
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2195.69 | 0.14199 | 9972.43ms | 7351818 | 30 | 6.16716e+08 | 3.19319e+06 | 0.914805 | 1.12756 | 1(Win) | true |
| Jsonifier | 2073.22 | 0.12425 | 5830.07ms | 7351818 | 80 | 1.41249e+09 | 3.38182e+06 | 0.117882 | 1.19416 | 2(Loss) | true |
| Glaze | 751.788 | 0.49546 | 6574.88ms | 7351818 | 40 | 8.54038e+10 | 9.32609e+06 | 1.74955 | 3.29316 | 3(Loss) | true |
| simdjson (ondemand) | 483.606 | 1.53967 | 10044.6ms | 7351818 | 30 | 1.4948e+12 | 1.44978e+07 | 0.283992 | 5.11937 | 4(Loss) | true |
