
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11721.9 | 0.218715 | 734.166ms | 2632 | 640 | 140.384 | 214.136 | 0.0386878 | 0.523716 | 1.74891 | 0.251682 | 0.000387063 | 2.49335e-05 | 1.42477e-05 | 1(Win) | true |
| simdjson (reflection) | 8441.82 | 0.455321 | 742.403ms | 2632 | 640 | 1173.04 | 297.337 | 0.222315 | 0.68985 | 2.51824 | 0.401216 | 0.000382314 | 1.48414e-05 | 4.74924e-06 | 2(Loss) | true |
| Glaze | 5410.55 | 0.131014 | 761.211ms | 2632 | 320 | 118.216 | 463.922 | 0.018184 | 1.05261 | 3.59005 | 0.569529 | 0.000379939 | 3.91812e-05 | 1.5435e-05 | 3(Loss) | true |
