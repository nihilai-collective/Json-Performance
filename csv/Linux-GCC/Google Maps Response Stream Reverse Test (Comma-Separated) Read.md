
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 767.161 | 0.110055 | 8268.05ms | 4203058 | 40 | 1.32262e+09 | 5.22491e+06 | 0.662806 | 6.6794 | 29.8144 | 6.13158 | 0.0240868 | 0.088251 | 0.00450384 | 1(Win) | true |
| simdjson (ondemand) | 637.649 | 0.134821 | 9812.05ms | 4203058 | 30 | 2.1548e+09 | 6.28614e+06 | 0.575492 | 7.99849 | 32.2342 | 6.77609 | 0.0274741 | 0.10336 | 0.00227476 | 2(Loss) | true |
