
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1154.7 | 0.0986721 | 1131.31ms | 4926 | 1280 | 20627.5 | 4068.41 | 0.0373635 | 4.4813 | 17.1821 | 3.24239 | 0.00898691 | 7.21617e-05 | 2.5217e-05 | 1(Win) | true |
| simdjson (ondemand) | 989.539 | 0.0493728 | 1201.76ms | 4926 | 2560 | 14065 | 4747.47 | 0.0676558 | 5.21841 | 19.5077 | 3.39566 | 0.00991272 | 4.43279e-05 | 1.26878e-05 | 2(Loss) | true |
