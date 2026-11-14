
----
### Random Small Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13448.1 | 0.110605 | 756.777ms | 5094 | 640 | 102.171 | 361.242 | 0.0731519 | 0.426232 | 1.61622 | 0.263055 | 0.000196309 | 1.44165e-05 | 1.22693e-06 | 1(Win) | true |
| simdjson (reflection) | 8087.71 | 0.21479 | 780.93ms | 5094 | 4890 | 8139.64 | 600.667 | 0.0287885 | 0.683082 | 2.41186 | 0.355516 | 0.00019651 | 5.56812e-05 | 2.48899e-05 | 2(Loss) | true |
| Glaze | 4235.48 | 0.188079 | 842.705ms | 5094 | 160 | 744.585 | 1146.98 | 0.0691555 | 1.26015 | 5.15764 | 0.82764 | 0.000196309 | 8.46584e-05 | 5.5212e-05 | 3(Loss) | true |
