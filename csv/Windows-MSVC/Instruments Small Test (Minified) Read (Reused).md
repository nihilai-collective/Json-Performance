
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2486.68 | 0.162705 | 205.877ms | 4669 | 160 | 1358.1 | 1790.62 | 1.34298 | 1.21287 | 1(Win) | true |
| Jsonifier (two-stage) | 1594.52 | 0.198121 | 315.949ms | 4669 | 40 | 1224.36 | 2792.5 | 1.79222 | 1.89672 | 2(Loss) | true |
| Glaze | 1557.24 | 0.4099 | 307.438ms | 4669 | 4890 | 671744 | 2859.37 | 0.0208004 | 1.93727 | 3(Loss) | true |
| simdjson (ondemand) | 982.403 | 0.110011 | 480.916ms | 4669 | 2560 | 63646.9 | 4532.46 | 0.0559881 | 3.08166 | 4(Loss) | true |
