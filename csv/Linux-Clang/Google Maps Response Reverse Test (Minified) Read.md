
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.551 | 0.0194486 | 2166.1ms | 11812 | 4890 | 38622.7 | 14450.4 | 0.0175701 | 6.61965 | 30.0065 | 6.03061 | 0.0161588 | 2.67483e-05 | 7.15019e-06 | 1(Win) | true |
| simdjson (ondemand) | 689.698 | 0.0355725 | 2355.63ms | 11812 | 1280 | 43208.3 | 16332.9 | 0.0554929 | 7.4761 | 33.5294 | 6.17449 | 0.013618 | 2.32814e-05 | 7.34158e-06 | 2(Loss) | true |
