
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1516.39 | 0.108213 | 1320.78ms | 9378 | 320 | 13034.8 | 5897.91 | 0.0659566 | 3.41774 | 14.7165 | 2.89209 | 0.00618735 | 1.83275e-05 | 2.99904e-06 | 1(Win) | true |
| simdjson (ondemand) | 1426.08 | 0.0621381 | 1367.08ms | 9378 | 1280 | 19438.4 | 6271.44 | 0.133451 | 3.62108 | 15.9003 | 2.84059 | 0.00483362 | 5.28997e-05 | 2.54918e-05 | 2(Loss) | true |
