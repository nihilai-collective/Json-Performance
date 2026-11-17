
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3142.64 | 0.129965 | 811.274ms | 25388 | 4890 | 490265 | 7704.3 | 0.00579567 | 0.785102 | 1(Win) | true |
| Jsonifier (two-stage) | 3075.35 | 0.0322645 | 793.53ms | 25388 | 80 | 516.187 | 7872.88 | 1.09761 | 0.802257 | 2(Loss) | true |
| simdjson (reflection) | 2963.91 | 0.283936 | 889.983ms | 25388 | 640 | 344307 | 8168.89 | 0.225405 | 0.832618 | 3(Loss) | true |
| Glaze | 2666.95 | 0.0585576 | 939.077ms | 25388 | 30 | 847.845 | 9078.5 | 0.0741129 | 0.925754 | 4(Loss) | true |
| simdjson (ondemand) | 2438.17 | 0.276889 | 1043.54ms | 25388 | 640 | 483862 | 9930.35 | 0.0471343 | 1.01276 | 5(Loss) | true |
