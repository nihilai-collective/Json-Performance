
----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12698 | 0.113389 | 1169.78ms | 56369 | 1280 | 29496.1 | 4233.57 | 0.0299224 | 0.402555 | 1.49976 | 0.212333 | 0.000166786 | 1.64652e-05 | 8.60679e-06 | 1(Win) | true |
| Glaze | 5553.63 | 0.0902464 | 1707.6ms | 56369 | 2560 | 195356 | 9679.74 | 0.156473 | 0.919861 | 3.41113 | 0.467048 | 0.000109532 | 1.06372e-05 | 3.81138e-06 | 2(Loss) | true |
