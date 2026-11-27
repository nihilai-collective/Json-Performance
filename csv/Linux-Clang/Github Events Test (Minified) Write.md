
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14980.4 | 0.205066 | 1115.73ms | 58581 | 4890 | 285998 | 3729.35 | 0.0569213 | 0.342548 | 1.12782 | 0.158208 | 4.44493e-05 | 2.14584e-05 | 1.108e-05 | 1(Win) | true |
| Glaze | 4924.33 | 0.130319 | 1883.37ms | 58581 | 4890 | 1.06892e+06 | 11345.1 | 0.0137451 | 1.02994 | 2.62459 | 0.382326 | 7.44639e-05 | 4.16077e-05 | 2.02157e-05 | 2(Loss) | true |
