
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2558.09 | 0.208931 | 8581.66ms | 7351818 | 30 | 9.83756e+08 | 2.74081e+06 | 0.643129 | 1.94403 | 8.24515 | 1.55788 | 0.0119509 | 0.0618819 | 0.002106 | 1(Win) | true |
| Jsonifier | 2480.15 | 0.0817658 | 8797.47ms | 7351818 | 80 | 4.27434e+08 | 2.82695e+06 | 0.0122745 | 2.0247 | 8.67708 | 2.04263 | 0.00905924 | 0.0343554 | 0.000289893 | 2(Loss) | true |
| simdjson (reflection) | 2251.68 | 0.0585191 | 9696.99ms | 7351818 | 160 | 5.31242e+08 | 3.11379e+06 | 0.230063 | 2.23809 | 9.70704 | 1.6587 | 0.00910173 | 0.058516 | 0.000823936 | 3(Loss) | true |
| Glaze | 2072.47 | 0.0752704 | 5113.48ms | 7351818 | 80 | 5.18745e+08 | 3.38304e+06 | 0.0405384 | 2.43301 | 11.2347 | 2.23762 | 0.00905191 | 0.0336095 | 0.00118296 | 4(Loss) | true |
| simdjson (ondemand) | 1960.66 | 0.110159 | 5391.09ms | 7351818 | 80 | 1.24141e+09 | 3.57597e+06 | 0.0467393 | 2.55752 | 10.3588 | 1.86883 | 0.0102979 | 0.0613653 | 0.00129864 | 5(Loss) | true |
