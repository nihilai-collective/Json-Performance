
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 781.039 | 0.0534682 | 1269.28ms | 4390 | 160 | 1314.3 | 5360.33 | 0.0446368 | 6.64751 | 29.1993 | 5.90911 | 0.0112557 | 4.84055e-05 | 4.27107e-06 | 1(Win) | true |
| simdjson (ondemand) | 681.386 | 0.0566342 | 1347.99ms | 4390 | 1280 | 15499.2 | 6144.29 | 0.0540606 | 7.53939 | 32.9911 | 6.06697 | 0.0099774 | 7.15404e-05 | 3.63041e-05 | 2(Loss) | true |
