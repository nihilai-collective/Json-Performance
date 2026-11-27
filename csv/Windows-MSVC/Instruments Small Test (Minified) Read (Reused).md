
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1531.45 | 0.118876 | 309.601ms | 4669 | 80 | 955.696 | 2907.5 | 0.25729 | 1.60334 | 1(Win) | true |
| Jsonifier (two-stage) | 1109.02 | 0.168028 | 453.624ms | 4669 | 40 | 1820.51 | 4015 | 0.124688 | 2.22131 | 2(Loss) | true |
| Glaze | 1010.54 | 0.129845 | 521.012ms | 4669 | 80 | 2618.67 | 4406.25 | 0.198188 | 2.43618 | 3(Loss) | true |
| simdjson (ondemand) | 850.565 | 0.145895 | 569.295ms | 4669 | 40 | 2333.33 | 5235 | 0.159439 | 2.89737 | 4(Loss) | true |
