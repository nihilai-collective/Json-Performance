
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1565.91 | 0.154255 | 868.589ms | 11579 | 320 | 37864.8 | 7051.88 | 0.0531491 | 1.93487 | 1(Win) | true |
| Jsonifier | 1512.68 | 0.217188 | 889.781ms | 11579 | 320 | 80438.9 | 7300 | 0.0856898 | 2.00361 | 2(Loss) | true |
| simdjson (ondemand) | 882.853 | 0.22334 | 1418.66ms | 11579 | 4890 | 3.81599e+06 | 12507.9 | 0.00188344 | 3.43643 | 3(Loss) | true |
| Glaze | 784.509 | 0.201914 | 1565.89ms | 11579 | 4890 | 3.94991e+06 | 14075.8 | 0.189813 | 3.86893 | 4(Loss) | true |
