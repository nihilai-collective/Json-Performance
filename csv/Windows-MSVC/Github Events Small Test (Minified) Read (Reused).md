
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1468.27 | 0.129701 | 133.817ms | 1691 | 4890 | 9923.62 | 1098.34 | 0.0946748 | 2.03556 | 1(Win) | true |
| Glaze | 1400.03 | 0.305907 | 137.554ms | 1691 | 640 | 7946.4 | 1151.88 | 0.189548 | 2.13309 | 2(Loss) | true |
| Jsonifier (two-stage) | 1196.83 | 0.129251 | 160.951ms | 1691 | 4890 | 14831.9 | 1347.44 | 0.0306238 | 2.50568 | 3(Loss) | true |
| simdjson (ondemand) | 753.87 | 0.106779 | 243.085ms | 1691 | 2560 | 13356.9 | 2139.18 | 0.177441 | 3.99629 | 4(Loss) | true |
