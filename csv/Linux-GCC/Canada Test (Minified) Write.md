
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2097.9 | 0.0353096 | 6076.16ms | 2090326 | 320 | 3.60241e+07 | 950231 | 0.0224211 | 2.4468 | 7.77177 | 0.373354 | 0.00033621 | 0.0517397 | 7.6579e-05 | 1(Win) | true |
| simdjson (reflection) | 1591.86 | 0.12542 | 7919.08ms | 2090326 | 40 | 9.86752e+07 | 1.2523e+06 | 0.0965548 | 3.18874 | 10.1384 | 0.578353 | 0.00492014 | 0.0511321 | 0.000327341 | 2(Loss) | true |
| Glaze | 1463.81 | 0.0961356 | 8635.85ms | 2090234 | 320 | 5.48451e+08 | 1.36179e+06 | 0.0518504 | 3.43985 | 9.59421 | 0.598242 | 0.0117291 | 0.0698452 | 0.000336093 | 3(Loss) | true |
