
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8817.35 | 0.507915 | 58.8268ms | 5094 | 4890 | 38294.2 | 550.961 | 0.0610479 | 0.266309 | 1(Win) | true |
| Glaze | 2761.22 | 0.243247 | 185.87ms | 5094 | 160 | 2930.42 | 1759.38 | 0.392297 | 0.883505 | 2(Loss) | true |
