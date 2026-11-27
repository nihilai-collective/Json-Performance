
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 837.761 | 0.0625853 | 1350.07ms | 4630 | 640 | 6963.8 | 5270.61 | 0.0211031 | 6.18182 | 30.9881 | 6.00648 | 0.00280879 | 2.32856e-05 | 3.37473e-07 | 1(Win) | true |
| simdjson (ondemand) | 808.185 | 0.0304577 | 1366.54ms | 4630 | 4890 | 13540.8 | 5463.49 | 0.187013 | 6.33309 | 31.9471 | 5.6013 | 0.00336995 | 7.78244e-05 | 4.01048e-05 | 2(Loss) | true |
