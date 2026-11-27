
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 780.226 | 0.0986911 | 7998.25ms | 2090234 | 160 | 1.01725e+09 | 2.55491e+06 | 0.385205 | 6.52905 | 32.0432 | 6.35048 | 0.027566 | 0.104703 | 0.000332938 | 1(Win) | true |
| simdjson (ondemand) | 759.288 | 0.344528 | 8138.44ms | 2090234 | 80 | 6.54509e+09 | 2.62536e+06 | 0.00495624 | 6.65621 | 31.7773 | 5.65411 | 0.0226657 | 0.103679 | 0.00164086 | 2(Loss) | true |
