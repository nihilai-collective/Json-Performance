
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.903 | 0.122917 | 1298.07ms | 4630 | 160 | 8055.46 | 5772.64 | 0.111967 | 6.77624 | 33.1447 | 6.40151 | 0.00485016 | 4.58963e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 747.46 | 0.0382781 | 1315.38ms | 4630 | 2560 | 13089.7 | 5907.36 | 0.443282 | 6.86634 | 32.9512 | 5.79957 | 0.00349335 | 6.277e-05 | 2.36231e-05 | 2(Loss) | true |
