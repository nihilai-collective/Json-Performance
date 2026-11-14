
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14939.7 | 0.0893204 | 1104.75ms | 56369 | 1280 | 13222.4 | 3598.32 | 0.0635683 | 0.342291 | 1.41182 | 0.236478 | 0.000185247 | 9.07802e-06 | 4.17173e-06 | 1(Win) | true |
| Glaze | 5423.2 | 0.0912873 | 1738.7ms | 56369 | 4890 | 400406 | 9912.54 | 0.126382 | 0.935977 | 3.41113 | 0.467048 | 0.000113625 | 2.18143e-05 | 1.12319e-05 | 2(Loss) | true |
