
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19735.2 | 0.155085 | 3061.77ms | 475954 | 4890 | 6.22148e+06 | 22999.8 | 0.0407736 | 0.255983 | 1.01863 | 0.15262 | 0.000276962 | 9.86674e-05 | 6.1897e-06 | 1(Win) | true |
| Glaze | 7020.13 | 0.156711 | 7233.41ms | 475954 | 4890 | 5.02052e+07 | 64657.7 | 0.210126 | 0.717855 | 2.35134 | 0.334375 | 0.000346381 | 0.000484715 | 2.91985e-05 | 2(Loss) | true |
