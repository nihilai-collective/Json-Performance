
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2236.59 | 0.0799089 | 465.45ms | 9378 | 160 | 1633.65 | 3998.75 | 0.345044 | 1.09925 | 1(Win) | true |
| Jsonifier (two-stage) | 2099.43 | 0.202863 | 471.085ms | 9378 | 80 | 5974.68 | 4260 | 0.176367 | 1.17011 | 2(Loss) | true |
| Glaze | 1597.78 | 0.119458 | 620.298ms | 9378 | 40 | 1788.46 | 5597.5 | 0.0148898 | 1.54571 | 3(Loss) | true |
| simdjson (ondemand) | 1203.27 | 0.299584 | 868.235ms | 9378 | 2560 | 1.26933e+06 | 7432.73 | 0.318441 | 2.05033 | 4(Loss) | true |
