
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 950.516 | 0.0317679 | 1185.35ms | 4604 | 4890 | 10530.3 | 4619.3 | 0.182198 | 5.45472 | 23.0854 | 4.8662 | 0.00441796 | 4.75269e-05 | 1.66566e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 781.197 | 0.0376151 | 1288.73ms | 4604 | 160 | 715.145 | 5620.5 | 0.0155704 | 6.64677 | 26.8285 | 5.30115 | 0.00457754 | 2.17202e-05 | 0 | 2(Loss) | true |
| Glaze | 650.377 | 0.132948 | 1403.32ms | 4604 | 320 | 25778.2 | 6751.04 | 0.135351 | 7.96253 | 33.7815 | 6.94574 | 0.005333 | 3.66529e-05 | 1.08601e-05 | 3(Loss) | true |
| simdjson (reflection) | 637.535 | 0.134734 | 1422.03ms | 4604 | 40 | 3444.13 | 6887.02 | 0.0265061 | 8.13087 | 31.0805 | 5.98219 | 0.00502281 | 5.43006e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 486.125 | 0.0367024 | 1634.45ms | 4604 | 2560 | 28132.2 | 9032.08 | 0.0858224 | 10.5993 | 37.6409 | 7.66421 | 0.00870931 | 6.99969e-05 | 2.8423e-05 | 5(Loss) | true |
