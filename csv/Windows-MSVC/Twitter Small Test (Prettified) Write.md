
----
### Twitter Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7189.48 | 0.366142 | 60.9194ms | 4300 | 4890 | 21327.9 | 570.389 | 0.389202 | 0.32833 | 1(Win) | true |
| Glaze | 3335.15 | 0.681738 | 126.29ms | 4300 | 2560 | 179879 | 1229.57 | 0.790906 | 0.7248 | 2(Loss) | true |
