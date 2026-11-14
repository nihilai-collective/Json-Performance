
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3308.05 | 0.0655251 | 3532.48ms | 83958 | 320 | 80490.8 | 24204.2 | 0.233419 | 1.52513 | 7.41656 | 1.1339 | 0.00166274 | 7.81641e-06 | 3.49877e-06 | 1(Win) | true |
| Glaze | 3223.15 | 0.0508081 | 3571.7ms | 83958 | 2560 | 407820 | 24841.7 | 0.0517779 | 1.5662 | 8.47109 | 1.7268 | 0.0021639 | 1.46744e-05 | 7.84898e-06 | 2(Loss) | true |
| Jsonifier | 2768.23 | 0.061255 | 3985.68ms | 83958 | 30 | 9417.24 | 28924.1 | 0.0718608 | 1.82952 | 7.54458 | 1.52686 | 0.00375505 | 7.54345e-06 | 1.19107e-06 | 3(Loss) | true |
| simdjson (reflection) | 2582.21 | 0.0328586 | 4233.85ms | 83958 | 1280 | 132877 | 31007.8 | 0.0811441 | 1.95913 | 8.69532 | 1.39921 | 0.00239295 | 1.23201e-05 | 6.08563e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2320.34 | 0.0504949 | 4580.84ms | 83958 | 1280 | 388620 | 34507.2 | 0.074442 | 2.16744 | 9.09111 | 1.56117 | 0.00568727 | 1.2255e-05 | 5.83439e-06 | 5(Loss) | true |
