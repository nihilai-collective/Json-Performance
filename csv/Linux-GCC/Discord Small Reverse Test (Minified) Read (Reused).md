
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.569 | 0.0468615 | 1349.24ms | 4857 | 640 | 5131.53 | 6042.51 | 0.0543323 | 6.76301 | 28.1787 | 5.58164 | 0.00749595 | 3.4422e-05 | 7.07741e-06 | 1(Win) | true |
| simdjson (ondemand) | 245.667 | 0.0566988 | 2638.02ms | 4857 | 320 | 36571.2 | 18854.8 | 0.0377746 | 20.9924 | 105.15 | 22.1116 | 0.0487409 | 5.40457e-05 | 1.9302e-06 | 2(Loss) | true |
