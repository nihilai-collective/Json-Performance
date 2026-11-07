
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 448.796 | 0.268801 | 1020.93ms | 4604 | 30 | 20747.1 | 9783.33 | 0.10211 | 5.49684 | 1(Win) | true |
| Jsonifier (two-stage) | 428.673 | 0.190166 | 1028.53ms | 4604 | 2560 | 971231 | 10242.6 | 0.109192 | 5.75403 | 2(Loss) | true |
| Glaze | 162.868 | 0.420386 | 2751.76ms | 4604 | 160 | 2.05502e+06 | 26958.8 | 0.302297 | 15.1762 | 3(Loss) | true |
| simdjson (ondemand) | 96.7022 | 0.232678 | 4569.22ms | 4604 | 640 | 7.14312e+06 | 45404.5 | 0.0615611 | 25.5872 | 4(Loss) | true |
