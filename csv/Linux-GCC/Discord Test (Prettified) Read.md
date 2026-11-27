
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3223.47 | 0.0233913 | 3224.84ms | 83958 | 2560 | 86422.9 | 24839.3 | 0.111728 | 1.57304 | 7.26673 | 1.437 | 0.00188766 | 1.67169e-05 | 9.55649e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2559.35 | 0.0568591 | 3859.66ms | 83958 | 80 | 25313.7 | 31284.8 | 0.118846 | 1.97763 | 9.24089 | 1.53617 | 0.00241624 | 3.57322e-06 | 1.33996e-06 | 2(Loss) | true |
| Glaze | 2438.48 | 0.057687 | 4011.02ms | 83958 | 320 | 114813 | 32835.4 | 0.00328353 | 2.07419 | 10.0009 | 2.0785 | 0.00336623 | 2.11415e-05 | 1.09802e-05 | 3(Loss) | true |
| simdjson (reflection) | 2325.56 | 0.0695075 | 4175.55ms | 83958 | 320 | 183267 | 34429.8 | 0.165488 | 2.18143 | 9.62529 | 1.57688 | 0.00204652 | 1.73822e-05 | 9.34247e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1938.52 | 0.0226415 | 4869.8ms | 83958 | 2560 | 223890 | 41304.1 | 0.244057 | 2.6084 | 10.573 | 1.86305 | 0.00514907 | 1.7331e-05 | 9.33316e-06 | 5(Loss) | true |
