
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1386.17 | 0.537794 | 8345.51ms | 94653 | 4890 | 5.99762e+08 | 65120.7 | 0.698981 | 2.19168 | 1(Win) | true |
| Glaze | 1329.35 | 0.57747 | 9235.52ms | 94653 | 640 | 9.84079e+07 | 67904.1 | 1.07262 | 2.28533 | 2(Loss) | true |
| Jsonifier (two-stage) | 1209.51 | 0.481217 | 9336.63ms | 94653 | 2560 | 3.30197e+08 | 74632.1 | 0.747201 | 2.51194 | 3(Loss) | true |
| simdjson (ondemand) | 1064.7 | 0.771479 | 5344.32ms | 94653 | 40 | 1.71128e+07 | 84782.5 | 0.739663 | 2.85377 | 4(Loss) | true |
