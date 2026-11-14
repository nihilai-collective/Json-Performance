
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1319.57 | 0.0609612 | 1578.15ms | 11812 | 1280 | 34665.6 | 8536.72 | 0.0430404 | 3.91556 | 18.1246 | 3.5414 | 0.00497025 | 6.40239e-05 | 3.49221e-05 | 1(Win) | true |
| simdjson (ondemand) | 1035.24 | 0.107957 | 1802.56ms | 11812 | 30 | 4139.87 | 10881.3 | 0.0238999 | 4.99474 | 20.7117 | 3.5963 | 0.0095863 | 2.25759e-05 | 5.64398e-06 | 2(Loss) | true |
