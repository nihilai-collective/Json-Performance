
----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2400.71 | 0.0442282 | 1197.6ms | 11812 | 2560 | 11025.7 | 4692.27 | 0.0887807 | 2.15513 | 10.3996 | 1.86624 | 0.0033976 | 2.31491e-05 | 7.37465e-06 | 1(Win) | true |
| simdjson (ondemand) | 2067.85 | 0.101197 | 1276.54ms | 11812 | 320 | 9725.21 | 5447.6 | 0.0598672 | 2.50733 | 11.4714 | 1.83949 | 0.0032504 | 1.16407e-05 | 1.58737e-06 | 2(Loss) | true |
