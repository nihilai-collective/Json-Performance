
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 791.521 | 0.0381127 | 1285.85ms | 4630 | 4890 | 22104.7 | 5578.52 | 0.260481 | 6.50414 | 31.4203 | 5.76285 | 0.00436378 | 2.56618e-05 | 1.01145e-05 | 1(Win) | true |
| Jsonifier (generic) | 735.147 | 0.0619994 | 1324.93ms | 4630 | 80 | 1109.38 | 6006.3 | 0.110595 | 7.05583 | 31.2272 | 6.32829 | 0.00680076 | 2.15983e-05 | 0 | 2(Loss) | true |
