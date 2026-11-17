
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2172.62 | 0.0701849 | 1029.42ms | 6701 | 640 | 2727.6 | 2941.42 | 0.0387631 | 2.36609 | 9.16236 | 1.43232 | 0.00124095 | 2.33174e-05 | 6.99522e-06 | 1(Win) | true |
| Glaze | 2031.48 | 0.0533188 | 1050.6ms | 6701 | 2560 | 7202.02 | 3145.77 | 0.353579 | 2.51922 | 10.4632 | 2.117 | 0.000157451 | 9.09962e-05 | 3.53259e-05 | 2(Loss) | true |
| simdjson (reflection) | 2009.59 | 0.0364889 | 1059.07ms | 6701 | 4890 | 6584.04 | 3180.03 | 0.227804 | 2.54033 | 9.78481 | 1.61424 | 0.000586733 | 6.20424e-05 | 2.8473e-05 | 3(Loss) | true |
| Jsonifier | 1925.42 | 0.152133 | 1067.49ms | 6701 | 40 | 1019.84 | 3319.05 | 0.127206 | 2.65878 | 9.24817 | 1.796 | 0.00168258 | 5.59618e-05 | 3.73079e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1620.08 | 0.0399085 | 1135.71ms | 6701 | 4890 | 12118.5 | 3944.61 | 0.109842 | 3.14875 | 10.847 | 1.9994 | 0.00119266 | 5.65187e-05 | 2.19727e-05 | 5(Loss) | true |
