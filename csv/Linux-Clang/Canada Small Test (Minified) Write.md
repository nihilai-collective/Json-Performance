
----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1949.5 | 0.10936 | 960.67ms | 4630 | 2560 | 15706.5 | 2264.95 | 0.0497982 | 2.64041 | 7.98359 | 0.456372 | 0.000396109 | 3.40004e-05 | 2.78415e-06 | 1(Win) | true |
| Glaze | 968.836 | 0.0410873 | 1192.25ms | 4630 | 4890 | 17146.9 | 4557.54 | 0.0423847 | 5.26604 | 9.76048 | 0.676459 | 0.000262934 | 7.48652e-05 | 2.8356e-05 | 2(Loss) | true |
