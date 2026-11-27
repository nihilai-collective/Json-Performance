
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1899.02 | 0.407877 | 5616.19ms | 7351818 | 80 | 1.81418e+10 | 3.69204e+06 | 2.38871 | 1(Win) | true |
| Jsonifier | 1699.23 | 1.04628 | 6068.02ms | 7351818 | 40 | 7.45482e+10 | 4.12612e+06 | 0.473662 | 2(Loss) | true |
| Jsonifier (two-stage) | 1644.47 | 0.624867 | 6301.73ms | 7351818 | 80 | 5.67808e+10 | 4.26352e+06 | 2.30031 | 3(Loss) | true |
| simdjson (ondemand) | 1593.76 | 0.173043 | 7184ms | 7351818 | 80 | 4.63599e+09 | 4.39919e+06 | 0.387164 | 4(Loss) | true |
| Glaze | 1394.33 | 1.14071 | 7957.57ms | 7351818 | 40 | 1.31604e+11 | 5.0284e+06 | 1.18358 | 5(Loss) | true |
