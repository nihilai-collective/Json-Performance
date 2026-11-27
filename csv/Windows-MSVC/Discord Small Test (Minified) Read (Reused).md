
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1684.36 | 0.379988 | 342.828ms | 4857 | 30 | 3275.86 | 2750 | 0.243013 | 1.45942 | 1(Win) | true |
| Glaze | 1264.63 | 0.473826 | 434.964ms | 4857 | 1280 | 385530 | 3662.73 | 1.61472 | 1.94378 | 2(Loss) | true |
| Jsonifier (two-stage) | 1214.89 | 0.315442 | 435.258ms | 4857 | 2560 | 370292 | 3812.7 | 0.18714 | 2.02191 | 3(Loss) | true |
| simdjson (ondemand) | 885.659 | 0.17047 | 592.957ms | 4857 | 40 | 3179.49 | 5230 | 0.127307 | 2.77931 | 4(Loss) | true |
