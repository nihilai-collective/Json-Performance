
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1544.01 | 0.737106 | 7431.94ms | 461466 | 640 | 2.82502e+09 | 285030 | 0.148331 | 3.27079 | 14.939 | 2.80837 | 0.00866833 | 0.0398425 | 5.8516e-05 | 1(Win) | true |
| simdjson (reflection) | 1176.3 | 0.197618 | 9763ms | 461466 | 640 | 3.4985e+08 | 374131 | 0.301417 | 4.28128 | 18.4618 | 3.18743 | 0.00989797 | 0.0617206 | 7.26083e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1134.09 | 0.392055 | 5062.92ms | 461466 | 320 | 7.40678e+08 | 388055 | 0.109247 | 4.49891 | 19.9238 | 3.43586 | 0.0209315 | 0.0814158 | 0.000540628 | 3(Loss) | true |
| Glaze | 1054.84 | 0.174588 | 5408.73ms | 461466 | 160 | 8.489e+07 | 417209 | 0.315774 | 4.81686 | 20.1344 | 3.93606 | 0.0241073 | 0.0368676 | 0.000114161 | 4(Loss) | true |
| simdjson (ondemand) | 989.317 | 0.305708 | 5758.93ms | 461466 | 320 | 5.91795e+08 | 444840 | 0.0676463 | 5.08626 | 20.1785 | 3.56355 | 0.0116163 | 0.0915716 | 0.000122002 | 5(Loss) | true |
