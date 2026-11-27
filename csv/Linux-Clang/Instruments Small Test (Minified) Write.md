
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15052.5 | 0.192634 | 32.1756ms | 4669 | 80 | 25.9771 | 295.812 | 0.0380453 | 0.150661 | 1(Win) | true |
| Glaze | 3963.37 | 0.0419094 | 115.63ms | 4669 | 640 | 141.88 | 1123.46 | 0.074184 | 0.610622 | 2(Loss) | true |
