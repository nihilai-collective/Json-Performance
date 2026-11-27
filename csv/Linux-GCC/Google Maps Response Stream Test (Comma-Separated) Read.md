
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.74 | 0.247181 | 5219.7ms | 4203058 | 40 | 2.53434e+09 | 3.22023e+06 | 0.0988524 | 4.08735 | 18.7647 | 3.65723 | 0.0179653 | 0.0882267 | 0.0061206 | 1(Win) | true |
| simdjson (ondemand) | 816.907 | 0.55472 | 7846.83ms | 4203058 | 80 | 5.92684e+10 | 4.90673e+06 | 0.444077 | 6.22378 | 23.8699 | 5.08231 | 0.0237008 | 0.102231 | 0.0076509 | 2(Loss) | true |
