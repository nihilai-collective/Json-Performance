
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 846.743 | 0.348609 | 8363.23ms | 4506446 | 30 | 9.39211e+09 | 5.07554e+06 | 0.425482 | 5.96775 | 26.7363 | 5.43394 | 0.0132015 | 0.0810863 | 0.00426377 | 1(Win) | true |
| simdjson (ondemand) | 456.764 | 0.214983 | 6950.22ms | 4506446 | 30 | 1.22749e+10 | 9.40899e+06 | 0.168405 | 11.0807 | 47.3576 | 8.49768 | 0.0360704 | 0.0856905 | 0.00925377 | 2(Loss) | true |
