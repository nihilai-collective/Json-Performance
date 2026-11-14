
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2914.08 | 0.0837474 | 845.993ms | 3808 | 1280 | 1394.25 | 1246.22 | 0.00714712 | 1.82449 | 6.42332 | 0.900473 | 0.000264451 | 2.0516e-05 | 4.1032e-06 | 1(Win) | true |
| simdjson (reflection) | 2558.32 | 0.192895 | 866.981ms | 3808 | 640 | 4798.51 | 1419.52 | 0.160633 | 2.0676 | 7.35662 | 1.00762 | 0.000275325 | 3.73392e-05 | 2.87224e-06 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 2378.58 | 0.0954834 | 872.839ms | 3808 | 160 | 340.043 | 1526.79 | 0.00163745 | 2.22481 | 8.38157 | 1.51576 | 0.000490743 | 7.22164e-05 | 1.47715e-05 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 2375.82 | 0.153783 | 874.211ms | 3808 | 30 | 165.771 | 1528.57 | 0.0806206 | 2.22621 | 6.24133 | 1.14102 | 0.00121674 | 0.000122549 | 5.2521e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1710.65 | 0.0740512 | 935.636ms | 3808 | 160 | 395.416 | 2122.93 | 0.0612738 | 3.07932 | 9.52363 | 1.84769 | 0.00158548 | 9.19118e-05 | 2.29779e-05 | 5(Loss) | true |
