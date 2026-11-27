
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1984.6 | 0.0866221 | 956.606ms | 4918 | 2560 | 10728.2 | 2363.28 | 0.101731 | 2.64984 | 9.58662 | 0.794226 | 0.00060913 | 0.00012764 | 8.26047e-05 | 1(Win) | true |
| Jsonifier | 1585.21 | 0.534081 | 1020.33ms | 4918 | 80 | 19976.1 | 2958.71 | 0.0621433 | 3.35313 | 8.98516 | 0.468686 | 0.000282127 | 3.05002e-05 | 2.28752e-05 | 2(Loss) | true |
| Glaze | 1280.71 | 0.0538979 | 1066.71ms | 4604 | 4890 | 16696.3 | 3428.34 | 0.0126049 | 4.08252 | 12.2183 | 0.967203 | 0.000540741 | 7.71535e-05 | 3.15365e-05 | 3(Loss) | true |
