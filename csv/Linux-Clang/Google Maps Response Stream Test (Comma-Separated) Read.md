
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1104.3 | 0.461565 | 5882.41ms | 4203058 | 80 | 2.24549e+10 | 3.62976e+06 | 0.641998 | 4.59119 | 19.9748 | 3.82216 | 0.0196057 | 0.0884667 | 0.00934725 | 1(Win) | true |
| simdjson (ondemand) | 817.206 | 0.141832 | 7875.95ms | 4203058 | 30 | 1.45191e+09 | 4.90494e+06 | 0.035672 | 6.20949 | 24.2756 | 4.35384 | 0.0265182 | 0.104892 | 0.0123321 | 2(Loss) | true |
