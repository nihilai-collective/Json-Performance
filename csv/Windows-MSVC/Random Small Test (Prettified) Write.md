
----
### Random Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10634 | 0.437858 | 87.6628ms | 9255 | 160 | 2113.21 | 830 | 0 | 0.22424 | 1(Win) | true |
| Glaze | 3057.33 | 0.302866 | 303.54ms | 9255 | 4890 | 373832 | 2886.91 | 0.404354 | 0.802016 | 2(Loss) | true |
