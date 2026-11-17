
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 997.119 | 0.0701499 | 1088.67ms | 3862 | 1280 | 8594.01 | 3693.73 | 0.0132209 | 5.18354 | 27.1207 | 5.31409 | 0.00706443 | 4.77408e-05 | 5.25958e-06 | 1(Win) | true |
| Jsonifier | 947.58 | 0.093696 | 1106.74ms | 3862 | 80 | 1061.02 | 3886.84 | 0.176887 | 5.49465 | 26.1261 | 5.37002 | 0.00862571 | 5.50233e-05 | 1.29467e-05 | 2(Loss) | true |
| Glaze | 931.306 | 0.0670463 | 1117.82ms | 3862 | 2560 | 17998.2 | 3954.76 | 0.0905287 | 5.57191 | 28.6515 | 5.68799 | 0.00704612 | 9.2245e-05 | 4.31892e-05 | 3(Loss) | true |
