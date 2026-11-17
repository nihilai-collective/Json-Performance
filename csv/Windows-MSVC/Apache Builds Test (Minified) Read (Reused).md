
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1253.13 | 0.079312 | 8989.8ms | 94653 | 640 | 2.08898e+06 | 72034.1 | 0.392796 | 2.42462 | 1(Win) | true |
| Glaze | 1161.61 | 0.0968919 | 9508.13ms | 94653 | 4890 | 2.77226e+07 | 77709.6 | 0.0769971 | 2.61554 | 2(Loss) | true |
| Jsonifier (two-stage) | 1134.01 | 0.0892537 | 9744.44ms | 94653 | 320 | 1.61523e+06 | 79600.6 | 0.0212041 | 2.67924 | 3(Loss) | true |
| simdjson (ondemand) | 867.371 | 0.108202 | 6123.8ms | 94653 | 640 | 8.1154e+06 | 104071 | 0.0426574 | 3.5032 | 4(Loss) | true |
