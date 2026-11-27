
----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10987.9 | 0.824203 | 27.2858ms | 2866 | 640 | 2690.14 | 248.75 | 0.74813 | 0.199022 | 1(Win) | true |
| Glaze | 4043.85 | 0.587118 | 71.79ms | 2866 | 2560 | 40313.8 | 675.898 | 0.0636132 | 0.583136 | 2(Loss) | true |
