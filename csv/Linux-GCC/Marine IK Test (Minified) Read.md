
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 640.905 | 0.141207 | 8566.07ms | 1834197 | 40 | 5.94121e+08 | 2.72931e+06 | 0.162844 | 7.93695 | 32.4902 | 7.02838 | 0.0429098 | 0.138999 | 0.000265743 | 1(Win) | true |
| simdjson (ondemand) | 623.133 | 0.120791 | 8798.14ms | 1834197 | 80 | 9.19795e+08 | 2.80715e+06 | 0.368913 | 8.19389 | 34.2355 | 6.13444 | 0.0378378 | 0.139065 | 0.001186 | 2(Loss) | true |
