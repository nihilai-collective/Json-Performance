
----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15013.8 | 0.169584 | 32.7436ms | 4669 | 160 | 40.4723 | 296.575 | 0.126604 | 0.150605 | 1(Win) | true |
| simdjson (reflection) | 9876.52 | 0.1162 | 47.6834ms | 4669 | 160 | 43.9105 | 450.837 | 0.00277269 | 0.236013 | 2(Loss) | true |
| Glaze | 2163.06 | 0.147682 | 209.516ms | 4669 | 80 | 739.366 | 2058.53 | 0.0072873 | 1.13028 | 3(Loss) | true |
