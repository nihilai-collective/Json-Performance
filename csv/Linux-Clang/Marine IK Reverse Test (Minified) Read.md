
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 389.464 | 0.220971 | 6792.23ms | 1834197 | 30 | 2.95494e+09 | 4.49136e+06 | 0.0189488 | 12.9872 | 61.6091 | 13.5443 | 0.0441317 | 0.344241 | 0.00481679 | 1(Win) | true |
| simdjson (ondemand) | 270.858 | 0.131524 | 9656.12ms | 1834197 | 80 | 5.77181e+09 | 6.4581e+06 | 1.6404 | 18.7684 | 104.93 | 21.1332 | 0.0396321 | 0.789266 | 0.0368776 | 2(Loss) | true |
