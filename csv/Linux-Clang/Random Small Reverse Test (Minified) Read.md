
----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 832.165 | 0.0924914 | 1292.73ms | 4926 | 640 | 17448.3 | 5645.27 | 0.0190461 | 6.22806 | 26.8603 | 5.46143 | 0.00870984 | 8.59597e-05 | 4.409e-05 | 1(Win) | true |
| simdjson (ondemand) | 451.228 | 0.0229582 | 1768.86ms | 4926 | 4890 | 27937.1 | 10411.1 | 0.0185143 | 11.413 | 49.1975 | 8.94032 | 0.0294085 | 9.6562e-05 | 4.44202e-05 | 2(Loss) | true |
