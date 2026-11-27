
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.119 | 0.0311565 | 1312.73ms | 4857 | 2560 | 7869.53 | 5627.37 | 0.107508 | 6.28977 | 27.0896 | 5.25921 | 0.00750512 | 5.76648e-05 | 2.48514e-05 | 1(Win) | true |
| simdjson (ondemand) | 231.155 | 0.0353782 | 2772.56ms | 4857 | 640 | 32164.8 | 20038.5 | 0.167754 | 22.3166 | 105.267 | 22.127 | 0.0487586 | 0.000168571 | 0.000104231 | 2(Loss) | true |
