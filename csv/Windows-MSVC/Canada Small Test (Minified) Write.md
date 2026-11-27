
----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1676.51 | 0.201996 | 261.054ms | 4630 | 80 | 2264.24 | 2633.75 | 0.333333 | 1.45764 | 1(Win) | true |
| Glaze | 885.732 | 0.275221 | 510.935ms | 4630 | 1280 | 240952 | 4985.16 | 0.328022 | 2.7774 | 2(Loss) | true |
