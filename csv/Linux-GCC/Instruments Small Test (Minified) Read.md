
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3189.94 | 0.217669 | 141.435ms | 4669 | 2560 | 23632.8 | 1395.86 | 0.125809 | 0.760713 | 1(Win) | true |
| Jsonifier (two-stage) | 2449.16 | 0.0595414 | 187.693ms | 4669 | 160 | 187.487 | 1818.06 | 0.183581 | 0.99652 | 2(Loss) | true |
| Glaze | 1679.65 | 0.0847533 | 277.716ms | 4669 | 40 | 201.922 | 2650.97 | 0.113609 | 1.45908 | 3(Loss) | true |
| simdjson (reflection) | 1658.02 | 0.0760316 | 273.421ms | 4669 | 80 | 333.54 | 2685.56 | 0.158971 | 1.47908 | 4(Loss) | true |
| simdjson (ondemand) | 1143.15 | 0.121615 | 393.62ms | 4669 | 4890 | 109729 | 3895.12 | 0.088613 | 2.15138 | 5(Loss) | true |
