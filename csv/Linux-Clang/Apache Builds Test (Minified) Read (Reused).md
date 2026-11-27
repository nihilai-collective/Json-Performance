
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2058.97 | 0.0283682 | 6370.59ms | 94653 | 2560 | 395981 | 43841.4 | 0.0547502 | 2.46227 | 11.2204 | 2.04762 | 0.00611581 | 7.70908e-06 | 4.39517e-06 | 1(Win) | true |
| simdjson (ondemand) | 1703.21 | 0.0442524 | 7292.83ms | 94653 | 640 | 352036 | 52998.9 | 0.0554328 | 2.97749 | 12.7174 | 2.22268 | 0.00786565 | 1.22157e-05 | 6.28942e-06 | 2(Loss) | true |
