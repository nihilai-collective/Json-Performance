
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.88 | 0.0507671 | 1569.31ms | 11812 | 160 | 2552.21 | 7867.12 | 0.0773191 | 3.617 | 17.1199 | 3.31349 | 0.00481131 | 2.27523e-05 | 5.29123e-06 | 1(Win) | true |
| simdjson (ondemand) | 1118.35 | 0.0322693 | 1785.56ms | 11812 | 2560 | 27046.4 | 10072.7 | 0.0907108 | 4.61029 | 19.6283 | 3.36421 | 0.00720583 | 3.6278e-05 | 1.36249e-05 | 2(Loss) | true |
