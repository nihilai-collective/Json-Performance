
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2110.44 | 0.0425238 | 947.1ms | 5094 | 4890 | 4685.41 | 2301.9 | 0.272489 | 2.47908 | 11.247 | 2.00039 | 0.00161295 | 0.000113691 | 6.24657e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1477.89 | 0.0870462 | 1048.7ms | 5094 | 80 | 654.972 | 3287.12 | 0.0251042 | 3.52879 | 16.2788 | 2.63585 | 0.00233608 | 3.43541e-05 | 2.45387e-06 | 2(Loss) | true |
| simdjson (reflection) | 1297.31 | 0.0517847 | 1106.4ms | 5094 | 2560 | 9626.62 | 3744.69 | 0.141115 | 3.99198 | 15.7892 | 2.56145 | 0.00322231 | 0.00013642 | 6.8785e-05 | 3(Loss) | true |
| Glaze | 1269.73 | 0.215279 | 1110.85ms | 5094 | 160 | 10854.8 | 3826.03 | 0.0102903 | 4.16775 | 17.4827 | 3.33118 | 0.00498626 | 5.03043e-05 | 0 | 4(Loss) | true |
| simdjson (ondemand) | 1077.7 | 0.0632651 | 1185.57ms | 5094 | 160 | 1301.29 | 4507.78 | 0.094331 | 4.82336 | 17.3153 | 2.8938 | 0.00462922 | 6.25736e-05 | 2.33117e-05 | 5(Loss) | true |
