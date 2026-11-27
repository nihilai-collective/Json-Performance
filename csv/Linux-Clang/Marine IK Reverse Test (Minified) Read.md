
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 418.801 | 0.183748 | 6300.67ms | 1834197 | 80 | 4.71206e+09 | 4.17675e+06 | 0.168454 | 5.91157 | 1(Win) | true |
| simdjson (ondemand) | 223.64 | 0.134788 | 5490.53ms | 1834197 | 30 | 3.33442e+09 | 7.82163e+06 | 0.118047 | 11.0704 | 2(Loss) | true |
