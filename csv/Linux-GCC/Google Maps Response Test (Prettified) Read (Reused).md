
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4209.93 | 0.0278276 | 1367.8ms | 25388 | 4890 | 12524.7 | 5751.14 | 0.159808 | 1.21168 | 5.88916 | 0.972389 | 0.00266863 | 1.25254e-05 | 4.71214e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3380.18 | 0.117045 | 1512.42ms | 25388 | 30 | 2108.64 | 7162.9 | 0.037215 | 1.50473 | 7.50886 | 1.09067 | 0.00275852 | 1.31296e-05 | 7.87774e-06 | 2(Loss) | true |
| simdjson (reflection) | 3227.28 | 0.0362305 | 1543.95ms | 25388 | 2560 | 18913.5 | 7502.25 | 0.148007 | 1.57494 | 6.45187 | 0.925477 | 0.0019784 | 1.03088e-05 | 2.95415e-06 | 3(Loss) | true |
| Glaze | 2586.27 | 0.145286 | 1720.73ms | 25388 | 40 | 7399.7 | 9361.7 | 0.143699 | 1.96404 | 8.91531 | 1.69497 | 0.0051678 | 5.12053e-05 | 3.34804e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2538.49 | 0.0747667 | 1746.3ms | 25388 | 30 | 1525.61 | 9537.9 | 0.045063 | 2.00169 | 8.37242 | 1.38455 | 0.00298698 | 4.98923e-05 | 1.70684e-05 | 5(Loss) | true |
