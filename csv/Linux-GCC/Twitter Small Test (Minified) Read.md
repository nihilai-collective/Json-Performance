
----
### Twitter Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2345.27 | 0.124275 | 838.683ms | 2821 | 40 | 81.2917 | 1147.12 | 0.0442941 | 2.26964 | 8.134 | 1.45445 | 0.000850762 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2039.06 | 0.118793 | 852.445ms | 2821 | 1280 | 3144.39 | 1319.39 | 0.215839 | 2.60261 | 9.42467 | 1.54839 | 0.000360854 | 5.5942e-05 | 1.93859e-05 | 2(Loss) | true |
