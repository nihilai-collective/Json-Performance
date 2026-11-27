
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8579.09 | 0.54705 | 44.1767ms | 2963 | 640 | 2077.86 | 329.375 | 0.189394 | 0.264972 | 1(Win) | true |
| Glaze | 4110.16 | 0.77029 | 75.214ms | 2963 | 40 | 1121.79 | 687.5 | 0.362319 | 0.582847 | 2(Loss) | true |
