
----
### Random Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16461.2 | 0.0683028 | 31.9993ms | 5094 | 640 | 26.0047 | 295.119 | 0.0466131 | 0.136993 | 1(Win) | true |
| simdjson (reflection) | 12764.5 | 0.107576 | 40.5427ms | 5094 | 80 | 13.41 | 380.587 | 0.134842 | 0.180585 | 2(Loss) | true |
| Glaze | 4167.2 | 0.0686436 | 120.763ms | 5094 | 40 | 25.6147 | 1165.78 | 0.0579349 | 0.580438 | 3(Loss) | true |
