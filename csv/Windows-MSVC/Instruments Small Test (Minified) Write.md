
----
### Instruments Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12256.9 | 0.528432 | 40.8897ms | 4669 | 640 | 2358.54 | 363.281 | 0.47089 | 0.188996 | 1(Win) | true |
| Glaze | 2687.75 | 0.555445 | 179.431ms | 4669 | 30 | 2540.23 | 1656.67 | 0.400802 | 0.904719 | 2(Loss) | true |
