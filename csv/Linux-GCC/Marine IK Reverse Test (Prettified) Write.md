
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6133 | 0.118615 | 5000.68ms | 9930848 | 80 | 2.6841e+08 | 1.54423e+06 | 2.17439 | 0.403683 | 1(Win) | true |
| Glaze DID NOT CONVERGE | 3750.67 | 0.16846 | 8164.36ms | 9930228 | 30 | 5.42767e+08 | 2.52493e+06 | 2.9951 | 0.660086 | -(Loss) | false |
| simdjson (reflection) | 191.745 | 0.999288 | 14865ms | 10018896 | 30 | 7.43866e+12 | 4.98306e+07 | 1.77372 | 12.912 | 3(Loss) | true |
