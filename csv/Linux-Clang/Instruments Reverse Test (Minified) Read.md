
----
### Instruments Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 631.396 | 0.0606239 | 8757.96ms | 108313 | 320 | 3.14771e+06 | 163598 | 0.086441 | 8.06521 | 36.7512 | 7.35903 | 0.0101643 | 2.80437e-05 | 1.77437e-05 | 1(Win) | true |
| simdjson (ondemand) | 236.938 | 0.0853334 | 5667.23ms | 108313 | 640 | 8.8575e+07 | 435960 | 0.221764 | 21.5297 | 99.9535 | 18.0914 | 0.0792099 | 0.00027911 | 0.000236612 | 2(Loss) | true |
