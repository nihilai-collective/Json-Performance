
----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11699.4 | 0.474093 | 77.9722ms | 9255 | 4890 | 62554.6 | 754.417 | 0.077195 | 0.202918 | 1(Win) | true |
| Glaze | 3596.82 | 0.649577 | 258.365ms | 9255 | 640 | 162614 | 2453.91 | 0.428444 | 0.679184 | 2(Loss) | true |
