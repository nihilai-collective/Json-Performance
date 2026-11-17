
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11542 | 0.10827 | 834.498ms | 11812 | 4890 | 5460.27 | 975.984 | 0.202817 | 0.453465 | 2.09118 | 0.342618 | 0.000133863 | 1.83689e-05 | 3.86076e-06 | 1(Win) | true |
| Glaze | 3863.56 | 0.123613 | 1032.63ms | 11812 | 2560 | 33253.4 | 2915.65 | 0.187668 | 1.32576 | 5.63989 | 0.823576 | 0.000353421 | 2.46704e-05 | 8.4329e-06 | 2(Loss) | true |
