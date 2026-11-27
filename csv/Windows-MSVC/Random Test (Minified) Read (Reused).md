
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 930.051 | 0.12635 | 6181.67ms | 409725 | 320 | 9.01725e+07 | 420132 | 0.077044 | 3.2676 | 1(Win) | true |
| simdjson (ondemand) | 754.853 | 0.468212 | 7456.5ms | 409725 | 40 | 2.34966e+08 | 517642 | 0.0500918 | 4.02611 | 2(Loss) | true |
