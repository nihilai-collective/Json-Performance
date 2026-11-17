
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2099.89 | 0.226999 | 805.215ms | 1691 | 40 | 121.563 | 767.975 | 0.00325521 | 2.5819 | 8.88232 | 1.44412 | 0.00118273 | 0.000147842 | 0 | 1(Win) | true |
| Glaze | 1959.97 | 0.0889887 | 810.687ms | 1691 | 4890 | 2621.6 | 822.799 | 0.0538868 | 2.71132 | 10.0727 | 1.97575 | 0.0011161 | 0.000144637 | 3.55545e-05 | 2(Loss) | true |
| simdjson (reflection) | 1821.25 | 0.13691 | 818.876ms | 1691 | 320 | 470.294 | 885.469 | 0.0480202 | 2.90642 | 9.87463 | 1.644 | 0.000899985 | 6.65287e-05 | 5.54406e-06 | 3(Loss) | true |
| Jsonifier (two-stage) | 1749.6 | 0.071998 | 819.384ms | 1691 | 2560 | 1127.43 | 921.731 | 0.0385928 | 3.02757 | 10.4181 | 1.65405 | 0.000594138 | 9.679e-05 | 1.80182e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1559.33 | 0.181855 | 835.754ms | 1691 | 1280 | 4527.6 | 1034.2 | 0.00808228 | 3.36612 | 10.6298 | 1.71082 | 0.000737822 | 9.4249e-05 | 1.89422e-05 | 5(Loss) | true |
