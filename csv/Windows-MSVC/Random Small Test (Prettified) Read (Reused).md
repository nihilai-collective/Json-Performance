
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1541.77 | 0.163955 | 622.198ms | 8051 | 40 | 2666.67 | 4980 | 0.0669792 | 1.59709 | 1(Win) | true |
| Jsonifier (two-stage) | 1298.39 | 0.169645 | 707.85ms | 8051 | 4890 | 492127 | 5913.5 | 0.484137 | 1.89681 | 2(Loss) | true |
| Glaze | 1115.99 | 0.09465 | 810.821ms | 8051 | 80 | 3392.41 | 6880 | 0.511322 | 2.20875 | 3(Loss) | true |
| simdjson (ondemand) | 765.689 | 0.216008 | 1139.13ms | 8051 | 2560 | 1.20109e+06 | 10027.6 | 0.0315435 | 3.22419 | 4(Loss) | true |
